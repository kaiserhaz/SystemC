/**
 * PCIX Bus Slave Interface
 */

/**
 * Define guard
 */
#ifndef PCIX_BUS_SLAVE_IF
#define PCIX_BUS_SLAVE_IF

/**
 * Includes
 */
#include "pcix_trans.h"

/**
 * PCIX Bus Master Interface Definition
 */
struct pcix_bus_slave_if: public sc_interface {

	virtual void receive_transaction(pcix_trans& _trans) = 0;
	virtual const sc_event& transaction_event(void) const = 0;
	virtual pcix_trans get_transaction(void) = 0;
	virtual void transaction_done(pcix_trans _trans) = 0;

};

#endif
