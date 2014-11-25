#include <systemc.h>
#include "../modules/ClkUnit.h"

void test_clk_unit()
{
	sc_set_time_resolution(1, SC_NS);

	sc_signal<bool> reset, enable_tx, enable_rx;
	sc_clock clk("clk",25,SC_NS);	// 40MHz
	
	ClkUnit ClkUnit_inst("ClkUnit");
		ClkUnit_inst.sys_clk(clk);
		ClkUnit_inst.reset(reset);
		ClkUnit_inst.enable_tx(enable_tx);
		ClkUnit_inst.enable_rx(enable_rx);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_clkunit");
	sc_write_comment(tf, "Simulation of Clk Unit");
	((vcd_trace_file*)tf)->set_time_unit(1, SC_NS);	// 10exp(-9) = 1 ns

	sc_trace(tf, clk, "clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,enable_tx,"enable_tx");
	sc_trace(tf,enable_rx,"enable_rx");

	cout << "simulation ..."  << endl;

	for (int i=0; i<5; i++)
	{
		sc_start(1, SC_MS);
		cout << ".";
	}
	cout << endl;

	sc_close_vcd_trace_file(tf);
}
