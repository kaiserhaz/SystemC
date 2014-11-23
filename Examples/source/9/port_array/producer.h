/**
 * 9.3.1 : Producer Structure
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

	sc_port< sc_fifo_out_if<int> > mess_out;
	int id;

	SC_HAS_PROCESS( producer );

	producer(sc_module_name p_inst_name, int p_id) : sc_module(p_inst_name), id(p_id) {

		SC_THREAD( p_thread );

	}

	void p_thread(void) {

		while(true) {
				
			wait(id + 10, SC_US);

			mess_out->write(47);

		}
	}

};

#endif
