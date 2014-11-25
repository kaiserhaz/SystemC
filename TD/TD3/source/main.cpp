/**
 * 10.2.5 : PCIX main
 */

/**
 * Includes
 */
#include <systemc.h>
#include "pcix_component.h"

int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(1, SC_NS);

	pcix_component pcix_0("pcix_0");

	sc_trace_file *tf = sc_create_vcd_trace_file("pcix_0_trace");
	sc_write_comment(tf, "PCIX Simulation Trace");

	sc_trace(tf, pcix_0.pcix_sig, "pcix_sig");

	sc_start();

	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
