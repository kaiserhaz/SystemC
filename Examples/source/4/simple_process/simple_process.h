/**
 * 4.3.1 : Simple Process Structure
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
#include <string>

/**
 * Simple Process Module Definition
 */
SC_MODULE( simple_process ) {

	/** Simple Process Constructor **/
	SC_CTOR( simple_process ) {

		// Thread declaration
		SC_THREAD( my_thread_process );

	}

	/** Simple Process Threads **/
	void my_thread_process(void);

};

#endif
