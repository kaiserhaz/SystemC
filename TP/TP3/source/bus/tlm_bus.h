#ifndef TLM_BUS_H
#define TLM_BUS_H

#include "../interface/master/tlm_master_bus_if.h"
#include "../interface/slave/tlm_slave_bus_if.h"
#include <systemc.h>

/**
 * TLM Bus Channel
 */

struct tlm_bus : public sc_prim_channel, public tlm_master_bus_if, public tlm_slave_bus_if {

	private: 
	
		sc_event rw2slave_ev;    // Read-Write to Slave event
		sc_event w2master_ev;    // Write to Master event
		sc_event int0_interrupt; // Interrupt0 event
		sc_event int1_interrupt; // Interrupt1 event

		int data;                // Data
		int addr;                // Address

		bool accesstype;         // Read-Write access type

		sc_mutex mutex;          // Channel access mutex

	public:
		
		/* Default constructor */
		tlm_bus(): sc_prim_channel(sc_gen_unique_name("TLM_BUS")), mutex("mutex") {}

		/* Overloaded constructor */
		tlm_bus(const char* name): sc_prim_channel(name), mutex("mutex") {}

		int read2slave (unsigned int addr_);              // Read data from Slave implementation
		void write2slave (unsigned int addr_, int data_); // Write data to Slave implementation
		const sc_event& int0_event();                     // Interrupt0 event implementation
		const sc_event& int1_event();                     // Interrupt1 event implementation
		const sc_event& rw_event();                       // Read-Write event from Master implementation
		const bool is_read() const;                       // Read test implementation
		const unsigned int getAddress() const;            // Address get implementation
		const int getData () const;                       // Data get implementation
		void senddata2master (int data_);                 // Send data to Master implementation
		void int0_notify();                               // Interrupt0 notify implementation
		void int1_notify();                               // Interrupt1 notify implementation

};

#endif