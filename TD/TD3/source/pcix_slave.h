/**
 * PCI Slave
 */

/**
 * Define guard
 */
#ifndef PCIX_SLAVE
#define PCIX_SLAVE

/**
 * Includes
 */
#include "pcix_bus.h"


/**
 * Event finder
 */
struct pcix_slave_if: public sc_port<pcix_bus_slave_if> {

	typedef pcix_bus_slave_if slave_if_t;

	sc_event_finder& transaction_event() const {

		return *new sc_event_finder_t<slave_if_t> (*this, &slave_if_t::transaction_event);
	
	}

};

/**
 * PCI Slave Definition
 */
SC_MODULE( pcix_slave ) {

	pcix_slave_if p_master;

	int** memory;

	SC_CTOR( pcix_slave ) {

		memory = new int*[8];
		for(int i=0; i<256; i++)
			memory[i] = new int[8];

		SC_THREAD(pcix_slave_thread);
			sensitive << p_master.transaction_event();

	}

	void pcix_slave_thread(void);

};

#endif
