#ifndef TEST_FOUR_BIT_COUNTER_H
#define TEST_FOUR_BIT_COUNTER_H

#include <iostream>
#include <systemc.h>
#include "four_bit_counter.h"
#include "memory_rtl.h"

SC_MODULE( test_four_bit_counter ) {

	sc_signal<sc_logic> t_clk, t_rst, t_up_down, t_load;
	sc_signal< sc_lv<4> > t_data_in, t_q;
	
	sc_clock sys_clk0;
	
	four_bit_counter four_bit_counter_inst;
	
	#ifdef MEMORY_RTL_H
	
	sc_signal<bool> t_clk2, t_en, t_rd, t_wr;
	sc_signal< sc_uint<4> > t_addr;
	sc_signal< sc_lv<WORD_SIZE> > t_d_in, t_d_out;
	
	memory_rtl mem_rtl_inst;

	SC_CTOR( test_four_bit_counter ) : t_clk("clk"), \
	                                   t_rst("rst"), \
									   t_up_down("up_down"), \
									   t_load("load"), \
									   t_data_in("data_in"), \
									   t_q("q"), \
									   t_clk2("clk2"),\
									   t_en("enable"), \
									   t_rd("rd"), \
									   t_wr("wr"), \
									   t_d_in("mem_data_in"), \
									   t_d_out("mem_data_out"), \
									   sys_clk0("sys_clk0", 1, SC_US), \
									   four_bit_counter_inst("four_bit_counter_inst", "work.four_bit_counter"), \
									   mem_rtl_inst("mem_rtl_inst")
	{
		SC_THREAD( test_bench );
			//dont_initialize();
	
		SC_METHOD( clock_assign );
			sensitive << sys_clk0;
			
		SC_METHOD( convertor );
			sensitive << t_q;
					
		SC_THREAD( test_memory_rtl );
		
		mem_rtl_inst.clk(t_clk2);
		mem_rtl_inst.enable(t_en);
		mem_rtl_inst.rd(t_rd);
		mem_rtl_inst.wr(t_wr);
		mem_rtl_inst.addr(t_addr);
		mem_rtl_inst.data_in(t_d_in);
		mem_rtl_inst.data_out(t_d_out);
		
		four_bit_counter_inst.clk(t_clk);
		four_bit_counter_inst.rst(t_rst);
		four_bit_counter_inst.up_down(t_up_down);
		four_bit_counter_inst.load(t_load);
		four_bit_counter_inst.data_in(t_data_in);
		four_bit_counter_inst.q(t_q);
	}
	
	#else

	SC_CTOR( test_four_bit_counter ) : t_clk("clk"), \
	                                   t_rst("rst"), \
									   t_up_down("up_down"), \
									   t_load("load"), \
									   t_data_in("data_in"), \
									   t_q("q"), \
									   sys_clk0("sys_clk0", 1, SC_US), \
									   four_bit_counter_inst("four_bit_counter_inst", "work.four_bit_counter")
	{
		SC_THREAD( test_bench );
			//dont_initialize();
	
		SC_METHOD( clock_assign );
			sensitive << sys_clk0;
				
		four_bit_counter_inst.clk(t_clk);
		four_bit_counter_inst.rst(t_rst);
		four_bit_counter_inst.up_down(t_up_down);
		four_bit_counter_inst.load(t_load);
		four_bit_counter_inst.data_in(t_data_in);
		four_bit_counter_inst.q(t_q);
	}
	
	#endif
	
	void clock_assign(void);
	
	void test_bench(void);	

	#ifdef MEMORY_RTL_H
	
	void convertor(void);
	
	void test_memory_rtl(void);
	
	#endif
	
};

#endif
