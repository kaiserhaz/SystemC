/**
 * PCIX Bus Master Interface
 */

/**
 * Define guard
 */
#ifndef PCIX_BUS_MASTER_IF
#define PCIX_BUS_MASTER_IF

/**
 * Includes
 */
#include "pcix_trans.h"

/**
 * PCIX Bus Master Interface Definition
 */
struct pcix_bus_master_if: public sc_interface {

	virtual void send_transaction(pcix_trans _trans) = 0;
	virtual bool write(int _addr, int* _data, int _length) = 0;
	virtual bool read(int _addr, int* _data, int _length) = 0;

};

#endif
