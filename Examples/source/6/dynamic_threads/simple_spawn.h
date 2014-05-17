/**
 * 6.5.1 : Simple Spawn Structure
 */

/**
 * Define guard
 */
#ifndef SIMPLE_SPAWN_H
#define SIMPLE_SPAWN_H

/**
 * Defines
 */
#define SC_INCLUDE_DYNAMIC_PROCESSES

/**
 * Includes
 */
#include <iostream>
#include <systemc.h>

/**
 * Non-member functions
 */
int spawned_thread();
int spawned_method();
int h(int a, int& b, const int& c);

/**
 * Simple Spawn Module Definition
 */
SC_MODULE( simple_spawn ) {

	// Simple Spawn Ports
	sc_in_clk clk; // Clock

	/** Cimple Spawn Constructor **/
	SC_CTOR( simple_spawn )
	{
		// Thread declaration
		SC_THREAD(main_thread);
	}

	/** Simple Spawn threads **/
	void main_thread(void);
	
	/** Simple Spawn functions **/
	void g();

};

#endif
