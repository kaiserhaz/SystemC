/**
 * 7.2.1 : Producer Structure
 */

/**
 * Define guard
 */
#ifndef PRODUCER_H
#define PRODUCER_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Producer Module Definition
 */
SC_MODULE( producer ) {

	/** Producer Member Declaration **/
	sc_fifo_out<int> fifo_out;
	sc_fifo_in<int> fifo_in;

	/** Producer Constructor **/
	SC_CTOR( producer ) {

		// Thread declaration
		SC_THREAD( P1_thread );

	}

	/** Producer Threads **/
	void P1_thread() {
		
		int value = 1;

		while(true) {

			wait(10, SC_MS);

			cout << sc_time_stamp() << " : Producer => Writing to fifo1" << endl;

			fifo_out->write(value++);

			cout << sc_time_stamp() << " : Producer => Waiting on fifo2" << endl;

			int val = fifo_in->read();

			cout << sc_time_stamp() << " : Producer => Reading fifo2 = " << val ;

			cout << endl;

		}

	}

};

#endif
