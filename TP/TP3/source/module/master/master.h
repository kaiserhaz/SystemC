#include "../../interface/master/tlm_master_bus_if.h"

/**
 * Event finder
 */

struct tlm_master_if: public sc_port<tlm_master_bus_if> {

	typedef tlm_master_bus_if master_if_t;

	sc_event_finder& int0_event() const {

		return *new sc_event_finder_t<master_if_t> (*this, &master_if_t::int0_event);
	
	}

	sc_event_finder& int1_event() const {

		return *new sc_event_finder_t<master_if_t> (*this, &master_if_t::int1_event);
	
	}

};

/**
 * Master module
 */

struct master : public sc_module {

	tlm_master_if p_slave;

	SC_HAS_PROCESS( master );

	master(sc_module_name name): sc_module(name) {

		SC_THREAD(master_thread);
		SC_METHOD(int0_method);
			sensitive << p_slave.int0_event();
			dont_initialize();
		SC_METHOD(int1_method);
			sensitive << p_slave.int1_event();
			dont_initialize();

	}

	void master_thread(void);
	void int0_method(void);
	void int1_method(void);

};
