/**
 * 10.1.4 : Peripheral Module
 */

/**
 * Define guard
 */
#ifndef PERIPHERAL
#define PERIPHERAL

/**
 * Includes
 */
#include<systemc.h>
#include"my_interrupt_out_if.h"

/**
 * Peripheral Module Definition
 */
SC_MODULE( peripheral ) {

	sc_port<my_interrupt_out_if> irq;

	SC_CTOR(peripheral) {

		SC_THREAD(peripheral_thread);
	
	}

	void peripheral_thread(void) {

		wait(1, SC_NS);

		for(unsigned i=0; i!=5; i++) {

			cout << name() << " : Sending IRQ event at ";
			cout << sc_time_stamp() << endl;

			irq->notify(SC_ZERO_TIME);

			wait(5,SC_NS);
		
		}
	
	}

};

#endif
