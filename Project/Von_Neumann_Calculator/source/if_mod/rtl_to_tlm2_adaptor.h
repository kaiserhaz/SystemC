/**
 * RTL-to-TLM2 Adaptor
 */

/** Include guard **/
#ifndef RTL_TO_TLM2_ADAPTOR_H
#define RTL_TO_TLM2_ADAPTOR_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

/** Includes **/
#include "..\vnc_inc.h"
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

/**
 * Adaptor channel generating TLM transactions from RTL signals
 * Initiator socket could interface another channel type (eg. DDR3)
 */

struct rtl_to_tlm2_adaptor: public sc_channel {

  /** TLM-2 simple initiator socket **/
  
  tlm_utils::simple_initiator_socket<rtl_to_tlm2_adaptor> rtt2a_socket;

  /** Module input/output ports **/

  sc_in<bool>                    CLK;         // Clock input
  sc_in<sc_logic>                RST_N;       // Reset, active low
  sc_in<sc_logic>                R_NW;        // R/W signal; R active low; pulsed
  sc_in< a_word_t >              ADDR;        // Address line
  sc_inout_rv<MEM_DATA_WORD_LEN> DATA;        // Data line

  /** Adaptor constructor **/

  SC_HAS_PROCESS( rtl_to_tlm2_adaptor );

  rtl_to_tlm2_adaptor(sc_module_name _name) : sc_module(_name),
	                                          addr(0), data(0),
											  cmd(tlm::TLM_IGNORE_COMMAND)
                                              { // Construct and name socket

    SC_METHOD(r_nw_monitor);                  // R_NW line monitor
		sensitive << R_NW;                    // Set sensitivity
		dont_initialize();                    // Inhibit method initialization

    SC_THREAD(write_thread);                  // Register adaptor channel thread

	SC_THREAD(read_thread);                   // Register read/write method
	
	trans = new tlm::tlm_generic_payload;     // Create new payload instance

  }

  private:

  /** Variables **/

  signed short data;                          // Internal data buffer
  uint64 addr;                                // Address word variable, used to interface between uint and sc_lv

  sc_buffer<sc_logic> _r_nw;                  // Read/write buffer
  
  tlm::tlm_generic_payload* trans;            // Generic payload instance
  tlm::tlm_command cmd;                       // TLM-2 generic payload transaction, reused across calls to b_transport

  /** Write thread **/

  void write_thread() {

	  while(true) {

		wait(CLK->posedge_event() | RST_N->negedge_event()); // On either events

		if(RST_N->read() == SC_LOGIC_0) {     // Reset case

			cout << sc_time_stamp() << " ADAPTOR: Reseting" << endl;

			mem_reset();                      // Call reset

		}

		else if(_r_nw.read() == SC_LOGIC_1) {
		
			cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'W' << endl;

			mem_write();                      // Call write

		}

	    
	  }

  }

  /** Read thread **/

  void read_thread() {

    while(true) {

        wait(_r_nw.negedge_event());          // Wait for buffer trigger
		
		if(RST_N->read() == SC_LOGIC_0) {

			cout << sc_time_stamp() << " ADAPTOR: Resetting " << endl;

		}

        else if(_r_nw.read() == SC_LOGIC_0) {

			cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'R' << endl;

			mem_read();                       // Call write

        }

    }

  }

  /** Read/write monitor **/

  void r_nw_monitor() {
	
	_r_nw.write(R_NW->read());                // Read read/write value from port

	//cout << sc_time_stamp() << " ADAPTOR: Read/write method triggered " << endl;

  }

  /** Methods **/

  // Sets up TLM2 payload
  void payload_setup(tlm::tlm_generic_payload* trans,
	                 tlm::tlm_command cmd,
					 signed short& data,
					 uint64 addr)
  {

	  // Initialize 8 out of the 10 TLM-2 attributes, byte_enable_length and extensions being unused
      trans->set_command(cmd);
	  trans->set_address(addr);
      trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));
      trans->set_data_length(16);
      trans->set_streaming_width(16);
      trans->set_byte_enable_ptr(0);
      trans->set_dmi_allowed(false);
      trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  }

  // Local b_transport used to execute the standard TLM2 procedures
  void local_b_transport() {

	  payload_setup(trans, cmd, data, addr);  // Payload setup

	  rtt2a_socket->b_transport(*trans, sc_time(SC_ZERO_TIME)); // Blocking transport call

	  // Initiator obliged to check response status and delay
	  if (trans->is_response_error())
	    SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

  }

  // Memory write procedure
  void mem_write() {

	  // Phase 0

      wait(1, SC_NS);

      // Phase 1

      wait(SC_ZERO_TIME);

      cmd = tlm::TLM_WRITE_COMMAND;           // Set command 

      addr = ADDR->read().to_uint64();        // Read address line
 
      data = DATA->read().to_uint64();        // Read data line

      local_b_transport();                    // Call local b_transport

	  wait(4, SC_NS);                         // Setup wait before writing

  }
  
  // Memory read procedure
  void mem_read() {

      // Phase 0

      wait(1, SC_NS);

      // Phase 1

      wait(SC_ZERO_TIME);

      cmd = tlm::TLM_READ_COMMAND;            // Set command 

      addr = ADDR->read().to_uint64();        // Read address line
      
      local_b_transport();                    // Call local b_transport

	  wait(1, SC_NS);

      // Phase 2

	  DATA->write(data);                      // Write data to line

	  wait(1, SC_NS);

      // Phase 3

      DATA->write(d_word_t('Z'));             // Reset line to high impedance

      wait(1, SC_NS);

  }

  // Memory reset procedure
  void mem_reset() {

	  cmd = tlm::TLM_IGNORE_COMMAND;          // Set command 

      addr = 0;                               // Read address line
 
      data = 0;                               // Read data line

      local_b_transport();                    // Call local b_transport

	  wait(4, SC_NS);

  }

};

#endif
