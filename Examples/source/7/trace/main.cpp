/**
 * 7.5 : Tracing
 */

/**
 * Includes
 */
#include <systemc.h>

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(1, SC_PS);

	sc_clock clock("clk", 1, SC_NS);
	
	// Shift reg is declared but not implemented
	sc_signal<int> shiftreg_in;
	sc_signal<int> shiftreg_out;

	sc_trace_file *tf = sc_create_vcd_trace_file("wave");
	
	sc_write_comment(tf, "Simulation of Shift Reg at Elaboration Time Resolution");

	sc_trace(tf, clock, "Clock");
	sc_trace(tf, shiftreg_in, "shiftreg_in");
	sc_trace(tf, shiftreg_out, "shiftreg_out");

	sc_start(30, SC_NS);

	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
