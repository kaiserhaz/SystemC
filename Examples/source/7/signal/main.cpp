/**
 * 7.3.3 : Signal Simulation
 */

/**
 * Includes
 */
#include <systemc.h>
#include "signal.h"

/**
 * Global vars
 */
char* simulation_name = "signal";

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	cout << " INFO: Elaborating " << simulation_name << endl;
	
	signal s_inst("s_inst");

	cout << " INFO: Simulating " << simulation_name << endl;

	sc_start();

	cout << " INFO: Post-processing " << simulation_name << endl;

	system("pause");

	return 0;

}
