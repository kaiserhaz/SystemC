/**
 * Memory module
 */

/** Include guard **/
#ifndef MEMORY_H
#define MEMORY_H

/** Includes **/
#include <systemc.h>
#include "gen_mem.h"
#include "../if_mod/rtl_to_tlm2_adaptor.h"

/** Memory module definition **/

SC_MODULE( memory ) {

	/** Input/Output ports **/

	sc_in<bool> CLK;
	sc_in<sc_logic> RST_N;
	sc_out< a_word_t > ADDR;
	sc_out< d_word_t > DATA;
	sc_in<sc_logic> R_NW;

	/** Submodule instances **/

	gen_mem* g_m0;
	rtl_to_tlm2_adaptor* rtt2a0;

	/** Memory constructor **/

	SC_CTOR( memory ) {

		g_m0 = new gen_mem("g_m0"); // Generic memory instance
		rtt2a0 = new rtl_to_tlm2_adaptor("rtt2a0"); // Adaptor instance

		rtt2a0->rtt2a_socket.bind(g_m0->mem_socket); // TLM socket bind

		// Port binding
		rtt2a0->CLK(CLK);
		rtt2a0->RST_N(RST_N);
		rtt2a0->ADDR(ADDR);
		rtt2a0->DATA(DATA);
		rtt2a0->R_NW(R_NW);

	}

};

#endif
