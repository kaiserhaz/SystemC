/**
 * PCI RTL Slave
 */

/**
 * Define guard
 */
#ifndef PCIX_RTL_SLAVE
#define PCIX_RTL_SLAVE

/**
 * Includes
 */
#include "pcix_trans.h"
#include "my_interrupt.h"

/**
 * PCI Slave Definition
 */
SC_MODULE( pcix_rtl_slave ) {

	sc_in<int> p_devnum;
	sc_in<int> p_addr;
	sc_in<int> p_attr1;
	sc_in<int> p_attr2;
	sc_in<int> p_cmnd;
	sc_port< sc_signal_in_if<int>, 8 > p_datain;
	sc_port<my_interrupt_in_if> p_tlm2rtl;

	sc_port< sc_signal_out_if<int>, 8 > p_dataout;
	sc_port<my_interrupt_out_if> p_rtl2tlm;

	int** memory;

	SC_CTOR( pcix_rtl_slave ) {

		memory = new int*[8];
		for(int i=0; i<256; i++)
			memory[i] = new int[8];

		SC_THREAD(pcix_slave_thread);
			sensitive << p_cmnd;

		SC_METHOD(rtl2tlm_int);
			sensitive << p_tlm2rtl;
			dont_initialize();

	}

	void pcix_slave_thread(void);
	void rtl2tlm_int(void);

	private:

		sc_event int_ev;

};

#endif
