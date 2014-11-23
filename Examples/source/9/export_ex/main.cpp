/**
 * 9.4.3 : Export Simulation
 */

/**
 * Includes
 */
#include "clock_gen.h"
#include "monitor.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	sc_signal<bool> c1;

	clock_gen c_gen_inst("c_gen_inst");
	monitor m_inst("m_inst");
		m_inst.clk1_p(c1);
		m_inst.clk2_p(c_gen_inst.clk2_p);

	// Connections
	
	c_gen_inst.clk1_p(c1);

	sc_start(50, SC_NS);

	system("pause");

	return 0;

}
