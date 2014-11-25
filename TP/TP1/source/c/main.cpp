#include <systemc.h>
#include "testbench/memory_rtl/test_memory_rtl.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> t_clk, t_enable, t_rd, t_wr;
	sc_signal< sc_uint<ADDR_SIZE> > t_addr;
	sc_signal< sc_lv<WORD_SIZE> > t_data_in, t_data_out;

	cout << " Signals declared " << endl;

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_memory_unit");
	sc_write_comment(tf, "Simulation of an RTL-described memory");
	tf->set_time_unit(1, SC_NS);	// 10exp(-9) = 1 ns

	cout << " Trace file setup complete " << endl;

	test_memory_rtl tm_rtl0_inst("tm_rtl0");
		tm_rtl0_inst.clk(t_clk);
		tm_rtl0_inst.enable(t_enable);
		tm_rtl0_inst.rd(t_rd);
		tm_rtl0_inst.wr(t_wr);
		tm_rtl0_inst.addr(t_addr);
		tm_rtl0_inst.data_in(t_data_in);
		tm_rtl0_inst.data_out(t_data_out);
	
	cout << " Testbench instance setup complete " << endl;

	memory_rtl mem_rtl0_inst("mem_rtl0");
		mem_rtl0_inst.clk(t_clk);
		mem_rtl0_inst.enable(t_enable);
		mem_rtl0_inst.rd(t_rd);
		mem_rtl0_inst.wr(t_wr);
		mem_rtl0_inst.addr(t_addr);
		mem_rtl0_inst.data_in(t_data_in);
		mem_rtl0_inst.data_out(t_data_out);

	cout << " Memory instance setup complete " << endl;

	sc_trace(tf, t_clk, "clk");
	sc_trace(tf, t_enable, "enable");
	sc_trace(tf, t_rd, "rd");
	sc_trace(tf, t_wr, "wr");
	sc_trace(tf, t_addr, "addr");
	sc_trace(tf, t_data_in, "data_in");
	sc_trace(tf, t_data_out, "data_out");

	cout << " Tracer position setup complete " << endl;

	cout << " Start simulation " << endl;

	sc_start(50, SC_US);

	sc_close_vcd_trace_file(tf);

	system("pause");
	return 0;
}