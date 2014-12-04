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

struct processor : public sc_module {

	tlm_master_if p_slave;

	char *mess;
	int cpt_car;
	bool boot_done;

	SC_HAS_PROCESS( processor );

	processor(sc_module_name name): sc_module(name) {

		SC_THREAD(boot_thread);
		SC_THREAD(tx_interrupt_thread);
		SC_THREAD(rx_interrupt_thread);

	}

	// Processes
	void boot_thread();
	void tx_interrupt_thread();
	void rx_interrupt_thread();

};
