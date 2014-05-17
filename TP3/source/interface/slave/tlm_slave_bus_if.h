#ifndef TLM_SLAVE_BUS_IF_H
#define TLM_SLAVE_BUS_IF_H

#include <systemc.h>

/**
 * TLM Slave Bus Interface
 */

class tlm_slave_bus_if : virtual public sc_interface {

	public :

		virtual const sc_event& rw_event() const = 0;      // Read-Write event from Master
		virtual const bool is_read() const = 0;            // Read test; return true if read
		virtual const unsigned int getAddress() const = 0; // Get address from transaction
		virtual const int getData() const = 0;             // Get data from transaction
		virtual void senddata2master(int data_) = 0;       // Send data to Master
		virtual void int0_notify() const = 0;              // Interrupt0 notify
		virtual void int1_notify() const = 0;              // Interrupt1 notify

};

#endif