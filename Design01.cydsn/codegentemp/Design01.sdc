# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\164\Documents\psoc_mrubyc\sjc_mrubyc_boad\Design01.cydsn\Design01.cyprj
# Date: Tue, 04 Aug 2020 02:06:15 GMT
#set_units -time ns
create_clock -name {Clock_Tick(routed)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/dclk_3}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {ADC_2_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {ADC_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/aclk_glb_1}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 55} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 157 313} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Clock_Tick} -source [get_pins {ClockBlock/clk_sync}] -edges {1 24001 48001} [list [get_pins {ClockBlock/dclk_glb_3}]]


# Component constraints for C:\Users\164\Documents\psoc_mrubyc\sjc_mrubyc_boad\Design01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\164\Documents\psoc_mrubyc\sjc_mrubyc_boad\Design01.cydsn\Design01.cyprj
# Date: Tue, 04 Aug 2020 02:06:07 GMT
