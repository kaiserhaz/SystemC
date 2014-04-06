/**
 * 5.4.1 : Simple Process Structure
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

	/** Simple Process Constructor **/
	SC_CTOR( simple_process )
	{
		cout << " Constructor :" << name() << endl;
		
		// Thread declaration
		SC_THREAD( my_thread_process );
	}

	/** Simple Process Threads **/
	void my_thread_process(void) {

		cout << " my_thread_process executed within " << name() << endl;
	
	}

	/** Simple Process Kernel Phases **/

	// Before the end of the elaboration phase
	void before_end_of_elaboration() {

		cout << " before_end_of_elaboration : " << name() << endl;

	}

	// At the end of the elaboration phase
	void end_of_elaboration() {

		cout << " end_of_elaboration : " << name() << endl;

	}

	// At the start of the simulation phase
	void start_of_simulation() {

		cout << " start_of_simulation : " << name() << endl;

	}

	// At the end of the simulation phase
	void end_of_simulation() {

		cout << " end_of_simulation : " << name() << endl;

	}

};

#endif
