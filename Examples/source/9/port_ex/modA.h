/**
 * 9.1.1 : modA Structure
 */

/**
 * Define guard
 */
#ifndef MODA_H
#define MODA_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * modA Module Definition
 */
SC_MODULE( modA ) {

	/** modA Ports **/
	sc_port< sc_fifo_out_if<int> > fifo_o1;
	sc_port< sc_fifo_out_if<int> > fifo_o2;

	/** modA Constructor **/
	SC_CTOR( modA ) {

		// Thread declaration
		SC_THREAD( modA_thread );

	}

	/** modA Threads **/
	void modA_thread(void) {
		
		int val = 0;

		while(true) {

			fifo_o1->write(val);
			fifo_o2->write(-val);

			cout << sc_time_stamp() << " modA : writting value = " << val << endl;

			val = val + 5;

			wait(1, SC_MS);

		}

	}

};

#endif
