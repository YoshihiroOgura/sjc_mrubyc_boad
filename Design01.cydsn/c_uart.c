/*! @file
  @brief
  UART class for Cypress PSoC5LP

  <pre>
  Copyright (C) 2018 Kyushu Institute of Technology.
  Copyright (C) 2018 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.

  (Usage)
  PSoC Creator で、以下の通りUARTデバイスを設置
    * Communication > UARTデバイス配置
    * Configureダイアログを開く
    * Nameが"UART_1"であることを確認
    * 通信速度等のパラメータ設定
    * 同ダイアログAdvancedタブのInterruptを、"RX- On Byte Received"と
      "TX - On TX Complete"にチェックを入れる
    * System > Interrupt デバイスを2つ配置
    * UARTのtx_interruptとrx_interruptに接続
    * 名前をそれぞれ、"isr_UART_1_Tx"と、"isr_UART_1_Rx"に変更

  main.cに、以下の記述を追加。
    #include <c_uart.h>
    mrbc_init_class_uart(0);

  必要に応じて、UART_SIZE_RXFIFOマクロに、一行最大文字列を定義する。
  デフォルトは、128bytes。


  (on Ruby)
    uart1 = UART.new()
    uart.puts( "STRING\r\n" )
    s = uart.gets()

  </pre>
*/


#include "vm_config.h"
#include "mrubyc.h"
#include <stdint.h>
#include <project.h>	// auto generated by PSoC Creator.

#include "value.h"
#include "alloc.h"
#include "static.h"
#include "class.h"
#include "c_string.h"

#include "uart2.h"


//================================================================
/*! UART用設定
*/
#define NUM_UART 3
UART_HANDLE uh[NUM_UART];
UART_ISR( &uh[0], UART_1 );
UART_ISR( &uh[1], UART_2 );


//================================================================
/*! UART constructor
*/
static void c_uart_new(mrb_vm *vm, mrb_value v[], int argc)
{
  int num = GET_INT_ARG(1);

  if( num >= NUM_UART || num == 0 ) {
    *v = mrb_nil_value();
    return;
  }

  *v = mrbc_instance_new(vm, v->cls, sizeof(UART_HANDLE *));
  *((UART_HANDLE **)v->instance->data) = &uh[num-1];
}


//================================================================
/*! read
  s = $uart.read(n)
*/
static void c_uart_read(mrb_vm *vm, mrb_value v[], int argc)
{
  mrb_value ret;
  UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;
  int need_length = GET_INT_ARG(1);

  if( uart_bytes_available(handle) < need_length ) {
    ret = mrb_nil_value();
    goto DONE;
  }

  char *buf = mrbc_alloc( vm, need_length + 1 );
  uart_read( handle, buf, need_length );

  ret = mrbc_string_new_alloc( vm, buf, need_length );

 DONE:
  SET_RETURN(ret);
}


//================================================================
/*! write
  $uart.write(s)
*/
static void c_uart_write(mrb_vm *vm, mrb_value v[], int argc)
{
  UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;

  switch( v[1].tt ) {
  case MRBC_TT_STRING: {
    int n = uart_write( handle,
			mrbc_string_cstr(&v[1]), mrbc_string_size(&v[1]) );
    SET_INT_RETURN(n);
  } break;

  default:
    SET_NIL_RETURN();
    break;
  }
}


//================================================================
/*! gets
*/
static void c_uart_gets(mrb_vm *vm, mrb_value v[], int argc)
{
  mrb_value ret;
  UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;

  if( !uart_can_read_line( handle ) ) {
    ret = mrb_nil_value();
    goto DONE;
  }

  int len = uart_bytes_available( handle ) + 1;
  char *buf = mrbc_alloc( vm, len );

  len = uart_gets( handle, buf, len );
  mrbc_realloc( vm, buf, len );

  ret = mrbc_string_new_alloc( vm, buf, len );

 DONE:
  SET_RETURN(ret);
}


//================================================================
/*! puts
*/
static void c_uart_puts(mrb_vm *vm, mrb_value v[], int argc)
{
  char *s = NULL;
  switch( v[1].tt ) {
  case MRBC_TT_STRING: {
    s = mrbc_string_cstr(&v[1]);
  } break;

  default:
    break;
  }

  if( s ) {
    UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;
    uart_puts( handle, s );
  }
}


//================================================================
/*! clear_tx_buffer
*/
static void c_uart_clear_tx_buffer(mrb_vm *vm, mrb_value v[], int argc)
{
  UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;
  uart_clear_tx_buffer( handle );
}


//================================================================
/*! clear_rx_buffer
*/
static void c_uart_clear_rx_buffer(mrb_vm *vm, mrb_value v[], int argc)
{
  UART_HANDLE *handle = *(UART_HANDLE **)v->instance->data;
  uart_clear_rx_buffer( handle );
}


//================================================================
/*! initialize
*/
void mrbc_init_class_uart(struct VM *vm)
{
  // start physical device
  uart_init( &uh[0], UART_1 );
  uart_init( &uh[1], UART_2 );

  // define class and methods.
  mrb_class *uart;
  uart = mrbc_define_class(0, "UART",	mrbc_class_object);
  mrbc_define_method(0, uart, "new",	c_uart_new);
  mrbc_define_method(0, uart, "read",	c_uart_read);
  mrbc_define_method(0, uart, "write",	c_uart_write);
  mrbc_define_method(0, uart, "gets",	c_uart_gets);
  mrbc_define_method(0, uart, "puts",	c_uart_puts);
  mrbc_define_method(0, uart, "clear_tx_buffer", c_uart_clear_tx_buffer);
  mrbc_define_method(0, uart, "clear_rx_buffer", c_uart_clear_rx_buffer);
}

