/**
 * 6.1.2 : Simple Process Simulation
 */

/**
 * Includes
 */
#include "simple_process.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Instance creation
	simple_process my_instance("my_instance");

	// Start simulation
	sc_start(1, SC_SEC);

	system("pause");

	return 0;

}
