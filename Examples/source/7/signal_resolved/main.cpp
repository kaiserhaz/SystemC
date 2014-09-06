/**
 * 7.4.2 : Signal Resolved Simulation
 */

/**
 * Includes
 */
#include <systemc.h>
#include "signal_resolved.h"

/**
 * Global vars
 */
char* simulation_name = "signal_resolved";

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	cout << " INFO: Elaborating " << simulation_name << endl;
	
	signal_resolved s_rv_inst("s_rv_inst");

	cout << " INFO: Simulating " << simulation_name << endl;

	sc_start();

	cout << " INFO: Post-processing " << simulation_name << endl;

	system("pause");

	return 0;

}
