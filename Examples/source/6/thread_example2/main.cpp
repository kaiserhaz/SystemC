/**
 * 6.3.3 : Test Simulation
 */

/**
 * Includes
 */
#include "test.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Instance creation
	test t_inst("t_inst");

	// Start simulation
	sc_start(100, SC_NS);

	system("pause");

	return 0;

}
