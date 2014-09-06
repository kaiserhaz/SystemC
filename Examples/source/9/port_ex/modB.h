/**
 * 9.1.2 : modB Structure
 */

/**
 * Define guard
 */
#ifndef MODB_H
#define MODB_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * modB Module Definition
 */
SC_MODULE( modB ) {

	/** modB Ports **/
	sc_port< sc_fifo_in_if<int> > fifo_i1;
	sc_port< sc_fifo_in_if<int> > fifo_i2;

	/** modB Constructor **/
	SC_CTOR( modB ) {

		// Thread declaration
		SC_THREAD( modB_thread );

	}

	/** modB Threads **/
	void modB_thread(void) {
		
		int val;

		while(true) {

			fifo_i1->read(val);

			cout << sc_time_stamp() << " modB : reading value 1 = " << val << endl;

			fifo_i2->read(val);

			cout << sc_time_stamp() << " modB : reading value 2 = " << val << endl;

		}

	}

};

#endif
