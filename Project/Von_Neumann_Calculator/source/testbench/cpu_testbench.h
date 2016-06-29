/**
 * Von Neumann Calculator Testbench
 */

/** Include guard **/
#ifndef CPU_TESTBENCH_H
#define CPU_TESTBENCH_H

/** Includes **/
#include <systemc.h>
#include "../module/cpu.h"
#include "../module/memory.h"

/** Testbench module definition **/

SC_MODULE( cpu_testbench ) {

        /** Signal members **/

	sc_signal<sc_bit> t_clk, t_clkbus, t_rst, t_mw;
	sc_signal< sc_bv<16> > t_data, t_addr;
	
        /** Clocks **/

	sc_clock sys_clk0;
        sc_clock bus_clk0;
	
        /** Submodules **/

	cpu cpu_inst;
        memory mem_inst;

        /** Constructor **/

	SC_CTOR( cpu_testbench ) : t_clk("clk"), \
				   t_clkbus("clkbus"), \
	                           t_rst("rst"), \
				   t_mw("mw"), \
				   t_data("data"), \
				   t_addr("addr"), \
				   sys_clk0("sys_clk0", 10, SC_NS), \
				   bus_clk0("bus_clk0", 1.1, SC_NS), \
				   cpu_inst("cpu0", "work.cpu"), \
				   mem_inst("mem0")
	{
		SC_THREAD( test_bench );                     // Thread registration
	
		SC_METHOD( clock_assign1 );                  // Clock driver
			sensitive << sys_clk0;

		SC_METHOD( clock_assign2 );                  // Bus clock driver
			sensitive << bus_clk0;
				
                /** Submodule port connects **/

		cpu_inst.clk(t_clk);
		cpu_inst.rst(t_rst);
                cpu_inst.clkbus(t_clkbus);
		cpu_inst.datainout(t_data);
		cpu_inst.mw(t_mw);
		cpu_inst.addrout(t_addr);

		mem_inst.CLK(t_clkbus);
                mem_inst.RST_N(t_rst);
                mem_inst.R_NW(t_mw);
                mem_inst.ADDR(t_addr);
                mem_inst.DATA(t_data);

	}
	
        /** Methods **/

	void clock_assign1(void);
	void clock_assign2(void);

	void test_bench(void);	
	
};

#endif
