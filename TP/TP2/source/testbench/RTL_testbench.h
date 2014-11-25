#ifndef RTL_TESTBENCH_H
#define RTL_TESTBENCH_H

#include <systemc.h>

SC_MODULE(RTL_TestBench)
{
	// Port Declaration
	sc_out<bool> sys_clk, reset;

	sc_out<sc_logic> ce, rd, wr;
	sc_out<sc_lv<2> > addr;
	sc_in<sc_lv<8> > data_in;
	sc_out<sc_lv<8> > data_out;

	sc_in<bool> int_rx, int_tx;

	// Channel Members

	// Data Members
	sc_time CLK_PERIOD;	// 40 MHz
	char *mess;
	int cpt_car;
	bool boot_done;

	// Sub-modules
	sc_clock clock;
	sc_mutex bus_mutex;

	// Constructor
	SC_CTOR(RTL_TestBench) : CLK_PERIOD(25, SC_NS), clock("Clock", CLK_PERIOD),
		ce(false), rd(false), wr(false), addr(0), data_out("00000000"), cpt_car(0), boot_done(false)
	{
		SC_METHOD(sysclk_method);
			sensitive << clock.default_event();
		SC_THREAD(boot_thread);
		SC_THREAD(tx_interrupt_thread);
		SC_THREAD(rx_interrupt_thread);
	}

	// Processes
	void sysclk_method();
	void boot_thread();
	void tx_interrupt_thread();
	void rx_interrupt_thread();

	// Helper Functions
	void resetTest(void);
	void write(unsigned int addr, sc_uint<8> data);
	void read(unsigned int addr, sc_uint<8>& data);
};

#endif