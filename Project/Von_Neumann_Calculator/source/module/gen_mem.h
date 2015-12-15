/**
 * Generic memory instance
 */

/** Include guard **/
#ifndef GEN_MEM_H
#define GEN_MEM_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

/** Includes **/
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include "../vnc_dt.h"

/**
 * Simple generic memory instance
 * It is notable that we could customize the TLM socket to interface a channel (eg. DDR3)
 */

struct gen_mem: sc_module {
  
  /** TLM-2 simple target socket **/

  tlm_utils::simple_target_socket<gen_mem> mem_socket;

  /** Generic memory constructor **/

  SC_CTOR(gen_mem) : mem_socket("mem_socket") {

    // Register callback for incoming b_transport interface method call
    mem_socket.register_b_transport(this, &gen_mem::b_transport);

    // Initialize memory with random data
    for (int i = 0; i < MEM_SIZE; i++)
		mem[i] = 0;
  
  }

  // TLM-2 blocking transport method
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features
    if (adr >= sc_dt::uint64(MEM_SIZE) || byt != 0 || len > 16 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

    // Obliged to implement read and write commands
    if (cmd == tlm::TLM_READ_COMMAND) { // Read command
	  
	  memcpy(ptr, &mem[adr], len);

	  cout << "MEMORY: Reading value @" << adr << endl;

	}

    else if (cmd == tlm::TLM_WRITE_COMMAND) { // Write command

      memcpy(&mem[adr], ptr, len);

	  cout << "MEMORY: Writing value @" << adr << endl;

	}

	else { // Reset command

	  cout << "MEMORY: Reset requested" << endl;

	  for (int i = 0; i < MEM_SIZE; i++)
		mem[i] = 0;
	
	}

    // Obliged to set response status to indicate successful completion
    trans.set_response_status(tlm::TLM_OK_RESPONSE);

	// Realize wait delay to advance simulation time
	wait(delay);

  }

  private:

  unsigned short mem[MEM_SIZE]; // Memory array instance

};

#endif
