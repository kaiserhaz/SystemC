/**
 * 5.4.2 : Simple Process Simulation
 */

/**
 * Includes
 */
#include "simple_process.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	cout << " Start main() " << endl;

	// Instanciation of a simple_process object
	simple_process my_instance1("my_inst1");

	cout << " Before start() " << endl;

	// Run simulation for 100 ms
	sc_start(100, SC_MS);

	cout << " After start() " << endl;

	// Stop simulation; as in, run the stop routine
	sc_stop();

	cout << "After stop()" << endl;

	system("pause");

	return 0;
}
