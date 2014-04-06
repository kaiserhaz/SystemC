#ifndef MEMORY_RTL_H
#define MEMORY_RTL_H

#include <systemc.h>

#define MEM_SIZE 16
#define ADDR_SIZE 4
#define WORD_SIZE 8

SC_MODULE( memory_rtl ) {
	
	sc_in<bool> clk;
	sc_in<bool> enable;
	sc_in<bool> rd;
	sc_in<bool> wr;
	sc_in< sc_uint<ADDR_SIZE> > addr;
	sc_in< sc_lv<WORD_SIZE> > data_in;
	sc_out< sc_lv<WORD_SIZE> > data_out;
	
	sc_lv<WORD_SIZE> memory_case[MEM_SIZE];
	
	SC_CTOR( memory_rtl ) : clk("clk"), enable("enable"),
	                        rd("rd"), wr("wr"), addr("addr"),
							data_in("data_in"), data_out("data_out")
	{
		SC_THREAD( memory_process );
	}
	
	void memory_process(void) {
		
		sc_uint<ADDR_SIZE> temp_addr;
		
		while(true) {
			
			wait(clk.negedge_event());
			
			if(enable == true) {
				
				temp_addr = addr->read();
				
				if(rd == true) {
					
					data_out->write(memory_case[(int)temp_addr]);
				
				}
				else if(wr == true) {
					
					memory_case[(int)temp_addr] = data_in->read();
					
				}
				else {

					data_out->write("ZZZZZZZZ");

				}
				
			}
			else {

				data_out->write("ZZZZZZZZ");

			}

		}
				
	}
	
};

#endif