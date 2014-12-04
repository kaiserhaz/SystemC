#include "../../interface/slave/tlm_slave_bus_if.h"

/**
 * Event finder
 */

struct tlm_slave_if: public sc_port<tlm_slave_bus_if> {

	typedef tlm_slave_bus_if slave_if_t;

	sc_event_finder& rw_event() const {

		return *new sc_event_finder_t<slave_if_t> (*this, &slave_if_t::rw_event);
	
	}

};

/**
 * Slave module
 */

struct slave : public sc_module {
	
	tlm_slave_if p_master;
	sc_event addr_hi_hit, addr_lo_hit;
	int* memory;

	SC_HAS_PROCESS( slave );

	slave(sc_module_name name): sc_module(name) {

		memory = new int[32];

		SC_THREAD(slave_thread);
			sensitive << p_master.rw_event();
		SC_METHOD(int0_method);
			sensitive << addr_hi_hit;
			dont_initialize();
		SC_METHOD(int1_method);
			sensitive << addr_lo_hit;
			dont_initialize();

	}

	void slave_thread(void);
	void int0_method(void);
	void int1_method(void);

};
