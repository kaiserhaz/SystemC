/**
 * 6.2.1 : Architecture Structure
 */

/**
 * Define guard
 */
#ifndef ARCHI_EX_H
#define ARCHI_EX_H

/**
 * Includes
 */
#include <iostream>
#include <systemc.h>

/**
 * Architecture Module Definition
 */
SC_MODULE ( archi_ex ) {

	// Event declaration
	sc_event count, ok, restart, reset;

	// Message enumeration
	enum defmess { RESTART, OK, RESET, COUNT };

	// Message variable
	defmess from_usermess, from_countermess;

	// Counter variable
	int n;

	/** Architecture Constructor **/
	SC_CTOR( archi_ex ) : n(0)
	{
		// Thread declaration
		SC_THREAD( user_thread );

		SC_THREAD( counter_9_thread );
	}

	/** Architecture threads **/
	void user_thread(void);
	void counter_9_thread(void);

};

#endif