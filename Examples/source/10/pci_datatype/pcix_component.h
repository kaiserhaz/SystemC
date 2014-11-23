/**
 * 10.2.3 : PCI Component
 */

/**
 * Define guard
 */
#ifndef PCIX_COMPONENT
#define PCIX_COMPONENT

/**
 * Includes
 */
#include <systemc.h>
#include "pcix_trans.h"

/**
 * PCI Component Definition
 */
SC_MODULE( pcix_component ) {

	sc_signal<pcix_trans> pcix_sig;
	sc_fifo<pcix_trans> pcix_fifo;

	SC_CTOR( pcix_component ) {

		SC_THREAD(send_pcix_packet_thread);
		SC_METHOD(receive_pcix_packet_method);
			sensitive << pcix_sig;
			dont_initialize();

	}

	void send_pcix_packet_thread(void);
	void receive_pcix_packet_method(void);

};

#endif
