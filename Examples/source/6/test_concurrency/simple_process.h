/**
 * 6.1.1 : Simple Process Structure
 */

/**
 * Define guard
 */
#ifndef SIMPLE_PROCESS_H
#define SIMPLE_PROCESS_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Simple Process Module Definition
 */
SC_MODULE( simple_process ) {

	// State enumeration
	enum defstate {IDLE, RUN, STOP};

	// State variable
	defstate state;

	/** Simple Process Constructor **/
	SC_CTOR( simple_process ) : state(IDLE) {

		// Thread declaration
		SC_THREAD( p1_thread );

	}

	/** Simple Process Threads **/
	void p1_thread(void) {

		// Loop
		while(true) {
			
			// Wait statement
			// Commenting this line results in a simulation loop since the kernel
			//  does not get the turn to advance time
			wait(99, SC_MS);

			// Evaluate state
			switch(state) {
				
				// Idle state
				case IDLE : cout << " Idle : ";
							state = RUN;
							break;

				// Running state
				case RUN : cout << " Run : ";
						   state = STOP;
						   break;

				// Stop state
				case STOP : cout << " Stop : ";
							state = IDLE;
							break;

			}
			
			// Timestamp
			cout << sc_time_stamp() << endl;

		}

	}

};

#endif
