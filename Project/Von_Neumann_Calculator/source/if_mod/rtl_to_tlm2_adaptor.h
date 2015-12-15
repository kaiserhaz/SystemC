/**
 * RTL-to-TLM2 Adaptor
 */

/** Include guard **/
#ifndef RTL_TO_TLM2_ADAPTOR_H
#define RTL_TO_TLM2_ADAPTOR_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

/** Includes **/
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include "../vnc_dt.h"

/**
 * Adaptor module generating TLM transactions from RTL signals
 * Initiator socket could interface another channel type (eg. DDR3)
 */

struct rtl_to_tlm2_adaptor: sc_module {

  /** TLM-2 simple initiator socket **/
  
  tlm_utils::simple_initiator_socket<rtl_to_tlm2_adaptor> rtt2a_socket;

  /** Module input/output ports **/

  sc_in<bool> CLK;         // Clock input
  sc_in<sc_logic> RST_N;   // Reset, active low
  sc_out< a_word_t > ADDR; // Address line
  sc_out< d_word_t > DATA; // Data line
  sc_in<sc_logic> R_NW;    // R/W signal; R active low

  /** Adaptor constructor **/

  SC_CTOR(rtl_to_tlm2_adaptor) : rtt2a_socket("rtt2a_socket") { // Construct and name socket
  
    SC_THREAD(thread_process); // Register main process thread

  }

  private:

  /** Main process thread **/

  void thread_process() {

    // TLM-2 generic payload transaction, reused across calls to b_transport
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    tlm::tlm_command cmd;

	sc_time delay = sc_time(100, SC_US); // R/W delay

	uint64 addr;

    while(true) {

	  wait(CLK->posedge_event()); // Wait on CLK posedge event
	  
	  if(RST_N->read() == SC_LOGIC_0) { // Reset case

		  data = 0; // Write 0 to all cases

		  cmd = tlm::TLM_IGNORE_COMMAND; // Hacked use of this command. Normally we need to setup our own

          addr = 0; // Set 'null' addr

	  }

	  else {

		  if(R_NW->read() == SC_LOGIC_0) { // Read case

			  cmd = tlm::TLM_READ_COMMAND; // Set read command
		  
			  addr = ADDR->read().to_uint64(); // Set addr

			  data = DATA->read().to_uint(); // Set data

		  }

		  else if(R_NW->read() == SC_LOGIC_1) { // Write case

			  cmd = tlm::TLM_WRITE_COMMAND; // Set write command

			  addr = ADDR->read().to_uint64(); // Set addr

			  data = DATA->read().to_uint(); // Set data

		  }

		  else
			  SC_REPORT_ERROR("VNC", "R_NW Signal line error");
	  
	  }

	  // Initialize 8 out of the 10 TLM-2 attributes, byte_enable_length and extensions being unused
      trans->set_command(cmd);
	  trans->set_address(addr);
      trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));
      trans->set_data_length(16);
      trans->set_streaming_width(16);
      trans->set_byte_enable_ptr(0);
      trans->set_dmi_allowed(false);
      trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

      rtt2a_socket->b_transport(*trans, delay); // Blocking transport call

      // Initiator obliged to check response status and delay
      if (trans->is_response_error())
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

	  cout << "ADAPTOR: Command received: " << (cmd ? 'W' : 'R') << endl;

    }

  }

  // Internal data buffer
  unsigned short data;
  
};

#endif
