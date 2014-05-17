#ifndef TLM_MASTER_BUS_IF_H
#define TLM_MASTER_BUS_IF_H

#include <systemc.h>

/**
 * TLM Master Bus Interface
 */

class tlm_master_bus_if : virtual public sc_interface {

	public :

		virtual int read2slave(unsigned int addr_) = 0;              // Read data from Slave
		virtual void write2slave(unsigned int addr_, int data_) = 0; // Write data to Slave
		virtual const sc_event& int0_event() const = 0;              // Interrupt0 event
		virtual const sc_event& int1_event() const = 0;              // Interrupt1 event

};

#endif