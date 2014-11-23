/**
 * 9.3.2 : Consumer Structure
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

	sc_port< sc_fifo_in_if<int> > mess_in;
	int id;

	SC_HAS_PROCESS( consumer );

	consumer(sc_module_name c_inst_name, int c_id) : sc_module(c_inst_name), id(c_id) {

		SC_THREAD( c_thread );

	}

	void c_thread(void) {

		while(true) {

			wait(mess_in->data_written_event());

			cout << " Received " << mess_in->read() << " " << endl;

		}
	}

};

#endif
