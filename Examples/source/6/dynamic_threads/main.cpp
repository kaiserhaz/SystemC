/**
 * 6.5.3 : Simple Spawn Simulation
 */

/**
 * Includes
 */
#include "simple_spawn.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {
	
	// Clock variable declaration
	sc_clock t_clk("t_clk", 100, SC_NS);

	// Instance creation
	simple_spawn ss_inst("ss_inst");
		ss_inst.clk(t_clk);

	// Start simulation
	sc_start(300, SC_NS);

	system("pause");

	return 0;

}
