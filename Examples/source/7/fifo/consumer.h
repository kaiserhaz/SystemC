/**
 * 7.2.2 : Consumer Structure
 */

/**
 * Define guard
 */
#ifndef CONSUMER_H
#define CONSUMER_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Consumer Module Definition
 */
SC_MODULE( consumer ) {

	/** Consumer Member Declaration **/
	sc_fifo_out<int> fifo_out;
	sc_fifo_in<int> fifo_in;

	/** Consumer Constructor **/
	SC_CTOR( consumer ) {

		// Thread declaration
		SC_THREAD( P2_thread );

	}

	/** Consumer Threads **/
	void P2_thread() {

		while(true) {

			cout << sc_time_stamp() << " : Consumer => Waiting on fifo1" << endl;

			int val = fifo_in->read();

			cout << sc_time_stamp() << " : Consumer => Reading fifo1 = " << val << endl;

			wait(4, SC_MS);

			cout << sc_time_stamp() << " : Consumer => Writing to fifo2" << endl;

			fifo_out->write(val*2);

		}

	}

};

#endif
