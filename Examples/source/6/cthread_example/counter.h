/**
 * 6.4.1 : Counter Structure
 */

/**
 * Define guard
 */
#ifndef COUNTER_H
#define COUNTER_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Counter Module Definition
 */
SC_MODULE( counter ) {

	// Counter ports
	sc_in<bool> reset; // Reset
	sc_in_clk clk;     // Clock

	// Counter members
	int count;
	
	/** Counter Constructor **/
	SC_CTOR( counter ) : count(0)
	{
		// Clocked thread declaration
		SC_CTHREAD(counter_p_cthread, clk.pos());
			reset_signal_is(reset, true);
	}

	/** Counter Clocked Threads **/
	void counter_p_cthread() {

		// On reset...
		if(reset->read() == true) {

			cout << sc_time_stamp() << " : ";
			cout << " RESET ... " << endl;

			// Reset counter variable
			count = 0;
		}

		// Main loop
		while(true) {

			cout << sc_time_stamp() << " : ";
			cout << " count = " << count << endl;

			// Increase count value
			count++;
			
			// Wait for a clock cycle
			wait(1);

		}

	}

};

#endif
