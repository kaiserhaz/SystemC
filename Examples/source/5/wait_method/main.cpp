/**
 * 5.5.3 : Simple Process Simulation
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
	simple_process my_instance1("my_inst1");
	simple_process my_instance2("my_inst2");

	// Simulation start
	sc_start();

	system("pause");

	return 0;

}
