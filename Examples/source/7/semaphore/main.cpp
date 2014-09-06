/**
 * 7.1.2 : testsem Simulation
 */

/**
 * Includes
 */
#include "testsem.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Instance creation
	testsem t_sem_inst0("t_sem_inst0");

	// Simulation start
	sc_start(1, SC_SEC);

	system("pause");

	return 0;

}
