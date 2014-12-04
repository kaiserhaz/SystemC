/**
 * PCI Master
 */

/**
 * Define guard
 */
#ifndef PCIX_MASTER
#define PCIX_MASTER

/**
 * Includes
 */
#include "pcix_bus.h"

/**
 * PCI Component Definition
 */
SC_MODULE( pcix_master ) {

	sc_port<pcix_bus_master_if> p_slave;

	SC_CTOR( pcix_master ) {

		SC_THREAD(pcix_master_thread);

	}

	void pcix_master_thread(void);

};

#endif
