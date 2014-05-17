/**
 * 6.3.1 : Test Structure
 */

/**
 * Define guard
 */
#ifndef TEST_H
#define TEST_H

/**
 * Includes
 */
#include <iostream>
#include <systemc.h>

/**
 * Test Module Definition
 */
SC_MODULE ( test ) {

	// Time constants declaration
	const sc_time t1;
	const sc_time t2;
	const sc_time t3;

	/** Architecture Constructor **/
	SC_CTOR( test ) : t1(sc_time(10, SC_NS)), t2(sc_time(5, SC_NS)), t3(sc_time(15, SC_NS))
	{
		// Thread declaration
		SC_THREAD( Process_A );
		SC_THREAD( Process_B );
		SC_THREAD( Process_C );
		SC_THREAD( Process_D );

	}

	/** Architecture threads **/
	void Process_A(void);
	void Process_B(void);
	void Process_C(void);
	void Process_D(void);

};

#endif