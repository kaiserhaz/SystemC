/**
 * Memory module
 */

/** Include guard **/
#ifndef MEMORY_H
#define MEMORY_H

/** Includes **/
#include "gen_mem.h"
#include "../if_mod/rtl_to_tlm2_adaptor.h"

/** Memory module definition **/

SC_MODULE( memory ) {

	/** Input/Output ports **/

	sc_in<bool>                    CLK;       // Clock input
	sc_in<sc_logic>                RST_N;     // Reset input
	sc_in<sc_logic>                R_NW;      // Read/write input
	sc_in< a_word_t >              ADDR;      // Address line input
	sc_inout_rv<MEM_DATA_WORD_LEN> DATA;      // Data line bidirectional port

	/** Submodule instances **/

	gen_mem* g_m0;                            // Generic memory instance
	rtl_to_tlm2_adaptor* rtt2a0;              // RTL to TLM2 adaptor instance

	/** Memory constructor **/
	
	SC_HAS_PROCESS( memory );                 // Register 'memory' as a module constructor

	memory(sc_module_name _name) : sc_module(_name) {

		g_m0 = new gen_mem("g_m0");           // Generic memory instance
		rtt2a0 = new rtl_to_tlm2_adaptor("rtt2a0"); // Adaptor instance

		rtt2a0->rtt2a_socket.bind(g_m0->mem_socket); // TLM socket bind

		// Port binding
		rtt2a0->CLK(CLK);
		rtt2a0->RST_N(RST_N);
		rtt2a0->R_NW(R_NW);
		rtt2a0->ADDR(ADDR);
		rtt2a0->DATA(DATA);

	}

};

#endif
