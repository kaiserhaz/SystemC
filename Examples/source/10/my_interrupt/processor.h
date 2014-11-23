/**
 * 10.1.5 : Processor Module
 */

/**
 * Define guard
 */
#ifndef PROCESSOR
#define PROCESSOR

/**
 * Includes
 */
#include<systemc.h>
#include"my_interrupt_in_if.h"

/**
 * Processor Module Definition
 */
SC_MODULE( processor ) {

	sc_port<my_interrupt_in_if> irq;

	SC_CTOR(processor) {

		SC_METHOD(processor_method);
			sensitive << irq;
			dont_initialize();
	
	}

	void processor_method(void) {

		cout << name() << " : Received IRQ event at ";
		cout << sc_time_stamp() << endl;
	
	}

};

#endif
