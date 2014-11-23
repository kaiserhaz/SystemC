/**
 * 9.3.3 : Broadcast Channel Structure
 */

/**
 * Define guard
 */
#ifndef BROADCAST_H
#define BROADCAST_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Broadcast Channel Module Definition
 */
SC_MODULE( broadcast ) {
	
	sc_port<sc_fifo_in_if<int>, 5> mess_in;
	sc_port<sc_fifo_out_if<int>, 0> mess_out;

	SC_CTOR( broadcast ) {

		SC_THREAD(broadcast_thread);

	}

	void broadcast_thread(void) {
		
		int val = 0;
		int i = 0;
		int j = 0;

		while(true) {

			wait(mess_in[0]->data_written_event() |
				 mess_in[1]->data_written_event() |
				 mess_in[2]->data_written_event() |
				 mess_in[3]->data_written_event() |
				 mess_in[4]->data_written_event());
			
			for(i=0; i<mess_in.size(); i++) {
				
				if(mess_in[i]->nb_read(val) == true) {

					cout << sc_time_stamp() << " Send from Producer " << i << " to all consumer" << endl;

					for(j=0; j<mess_out.size(); j++) {

						mess_out[j]->write(val);

					}

				}

			}
		}
	}

};

#endif
