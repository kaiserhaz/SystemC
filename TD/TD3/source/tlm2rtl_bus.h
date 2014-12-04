/**
 * PCIX TLM2RTL Bus Adaptor
 */

/**
 * Define guard
 */
#ifndef TLM2RTL_BUS
#define TLM2RTL_BUS

/**
 * Includes
 */
#include "pcix_bus_slave_if.h"
#include "my_interrupt.h"

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
 * PCIX Bus Interface Definition
 */
struct tlm2rtl_bus: public sc_channel {

	pcix_slave_if p_master;

	sc_port< sc_signal_out_if<int> > p_devnum;
	sc_port< sc_signal_out_if<int> > p_addr;
	sc_port< sc_signal_out_if<int> > p_attr1;
	sc_port< sc_signal_out_if<int> > p_attr2;
	sc_port< sc_signal_out_if<int> > p_cmnd;
	sc_port< sc_signal_out_if<int>, 8 > p_dataout;
	sc_port<my_interrupt_out_if> p_tlm2rtl;
	
	sc_port< sc_signal_in_if<int>, 8 > p_datain;
	sc_port<my_interrupt_in_if> p_rtl2tlm;

	SC_HAS_PROCESS( tlm2rtl_bus );

	// Constructors
	tlm2rtl_bus() : sc_channel(sc_gen_unique_name("tlm2rtl_bus"))
	{

		SC_THREAD(tlm2rtl_thread);
			sensitive << p_master.transaction_event();

		SC_METHOD(tlm2rtl_int);
			sensitive << p_rtl2tlm;
			dont_initialize();

	}

	tlm2rtl_bus(sc_module_name nm) : sc_channel(nm)
	{

		SC_THREAD(tlm2rtl_thread);
			sensitive << p_master.transaction_event();

		SC_METHOD(tlm2rtl_int);
			sensitive << p_rtl2tlm;
			dont_initialize();

	}

	void tlm2rtl_thread(void);
	void tlm2rtl_int(void);

	private:

		sc_mutex rtl_mutex;
		sc_event int_ev;

		// Helper functions
		void rtl_write(pcix_trans _trans);
		pcix_trans rtl_read(pcix_trans __trans);

};

#endif
