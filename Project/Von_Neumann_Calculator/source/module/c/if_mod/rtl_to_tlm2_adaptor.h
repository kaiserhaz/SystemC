/**
 * RTL-to-TLM2 Adaptor
 */

/** Include guard **/
#ifndef RTL_TO_TLM2_ADAPTOR_H
#define RTL_TO_TLM2_ADAPTOR_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

/** Includes **/
#include "../../../vnc_inc.h"
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
  sc_in<bool>                    RST_N;       // Reset, active low
  sc_in<bool>                    R_NW;        // R/W signal; R active low; pulsed
  sc_in< a_word_t >              ADDR;        // Address line
  sc_in< d_word_t >              DATAIN;      // Data in line
  sc_out< d_word_t >             DATAOUT;     // Data out line

  /** Adaptor constructor **/

  SC_HAS_PROCESS( rtl_to_tlm2_adaptor );

  rtl_to_tlm2_adaptor(sc_module_name _name) : sc_module(_name),
	                                          _addr(0), _data(0)
                                              { // Construct and name socket

    SC_THREAD(write_thread);                  // Register write thread

	SC_THREAD(read_thread);                   // Register read thread (need this because method can't wait) 
	
  }

  private:
	  
  /** Variables **/

  signed short _data;                         // Internal data buffer
  uint64 _addr;                               // Address word variable, used to interface between uint and sc_lv

  /** Write thread **/

  void write_thread() {

	  tlm::tlm_generic_payload* wr_gp = new tlm::tlm_generic_payload; // Generic payload instance for write thread

	  while(true) {

		wait(CLK->posedge_event() | RST_N->default_event()); // On either events

		if(!RST_N->read()) {                  // Reset case

			cout << sc_time_stamp() << " ADAPTOR: Reseting" << endl;

			mem_reset(wr_gp);                 // Call reset

		}

		else if(R_NW->read()) {
		
			cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'W' << endl;

			mem_write(wr_gp);                 // Call write

		}

	  }

  }

  /** Read thread **/

  void read_thread() {

	tlm::tlm_generic_payload* rd_gp = new tlm::tlm_generic_payload; // Generic payload instance for read thread

    while(true) {

        wait(ADDR->value_changed_event());    // Wait for buffer trigger
		
		if(!RST_N->read()) {

			cout << sc_time_stamp() << " ADAPTOR: Resetting " << endl;

		}

        else if(!R_NW->read()) {

			cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'R' << endl;

			mem_read(rd_gp);                  // Call read

        }

    }

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
      trans->set_data_length(MEM_DATA_WORD_LEN);
      trans->set_streaming_width(MEM_DATA_WORD_LEN);
      trans->set_byte_enable_ptr(0);
      trans->set_dmi_allowed(false);
      trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  }

  // Local b_transport used to execute the standard TLM2 procedures
  void local_b_transport(tlm::tlm_generic_payload* trans,
						 tlm::tlm_command cmd,
					     signed short& data,
					     uint64 addr,
//						 sc_time &delay) {
						 sc_time delay) {


	  payload_setup(trans, cmd, data, addr);  // Payload setup

	  rtt2a_socket->b_transport(*trans, delay); // Blocking transport call

	  // Initiator obliged to check response status and delay
	  if (trans->is_response_error())
	    SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

  }

  // Memory write procedure
  void mem_write(tlm::tlm_generic_payload* _gp) {

      tlm::tlm_command _cmd = tlm::TLM_WRITE_COMMAND; // Set command 

      _addr = ADDR->read().to_uint64();       // Read address line
	  
      _data = DATAIN->read().to_uint64();     // Read data line

      local_b_transport(_gp, _cmd, _data, _addr, sc_time(MEM_DELAY, MEM_DELAY_UNIT)); // Call local b_transport

      wait(SC_ZERO_TIME);                     // Wait 1 delta for data to update

  }
  
  // Memory read procedure
  void mem_read(tlm::tlm_generic_payload* _gp) {

      tlm::tlm_command _cmd = tlm::TLM_READ_COMMAND; // Set command 

      _addr = ADDR->read().to_uint64();       // Read address line

	  _data = 0;                              // Null data
      
      local_b_transport(_gp, _cmd, _data, _addr, sc_time(MEM_DELAY, MEM_DELAY_UNIT)); // Call local b_transport

      DATAOUT->write(_data);                  // Write data to line

      wait(SC_ZERO_TIME);                     // Wait 1 delta for data to update

  }

  // Memory reset procedure
  void mem_reset(tlm::tlm_generic_payload* _gp) {

	  tlm::tlm_command _cmd = tlm::TLM_IGNORE_COMMAND; // Set command 

      _addr = 0;                               // Read address line
 
      _data = 0;                               // Read data line

      local_b_transport(_gp, _cmd, _data, _addr, sc_time(MEM_DELAY, MEM_DELAY_UNIT)); // Call local b_transport

	  wait(SC_ZERO_TIME);                     // Wait 1 delta for data to update

  }

};

#endif
