/**
 * 9.2.3 : Static Port Sensitivity Simulation
 */

/**
 * Includes
 */
#include "modA.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(100, SC_NS);

	sc_clock clk("clk", 1, SC_MS);
	sc_signal<int> cpt;

	modA modA_inst("modA");
		modA_inst.my_port(clk);
		modA_inst.cpt_o(cpt);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave");
	sc_write_comment(tf, "Simulation of Static Sensitivity");

	sc_trace(tf, clk, "clk");
	sc_trace(tf, cpt, "cpt");

	sc_start(20, SC_MS);

	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
