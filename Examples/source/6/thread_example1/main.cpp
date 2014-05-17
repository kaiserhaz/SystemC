/**
 * 6.2.3 : Architecture Simulation
 */

/**
 * Includes
 */
#include "archi_ex.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Instance creation
	archi_ex a_ex_inst("a_ex_inst");

	// Start simulation
	sc_start(100, SC_NS);

	system("pause");

	return 0;

}
