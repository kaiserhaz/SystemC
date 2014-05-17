/**
 * 6.4.2 : Counter Simulation
 */

/**
 * Includes
 */
#include <iostream>
#include "counter.h"

/**
 * Using namespace
 */
using namespace std;

/**
 * Main
 */
int sc_main(int argc, char* argv[]) {

	// Declaration of clk1
	sc_clock clk1("clk1", 10, SC_MS);

	// Declaration of the reset signal
	sc_signal<bool> rst;

	// Counter module instanciation and connection
	counter counter1("counter1");
		counter1.reset(rst);
		counter1.clk(clk1);

	/** Simulation **/

	// Assert reset
	rst.write(true);

	// Simulate for 1ms
	sc_start(1, SC_MS);

	// Deassert reset
	rst = false;

	// Simulate for 100ms
	sc_start(100, SC_MS);

	// Reassert reset
	rst = true;

	// Simulate for 12ms
	sc_start(12, SC_MS);

	// Re-deassert reset
	rst = false;

	// Simulate for 30ms
	sc_start(30, SC_MS);

	system("pause");

	return 0;

}