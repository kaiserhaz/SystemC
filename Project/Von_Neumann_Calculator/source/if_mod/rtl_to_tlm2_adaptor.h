/** ############################################################################################################
 *                                          CURRENTLY BEING REWORKED
 ** ############################################################################################################
 */

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

  sc_in<bool>                    CLK;           // Clock input
  sc_in<sc_logic>                RST_N;         // Reset, active low
  sc_in<sc_logic>                R_NW;          // R/W signal; R active low
  sc_out<sc_logic>               OR_N;          // Output ready, active low
  sc_out<sc_logic>               EOW_N;         // End of write, active low
  sc_in< a_word_t >              ADDR;          // Address line
  sc_inout_rv<MEM_DATA_WORD_LEN> DATA;          // Data line

  /** Adaptor constructor **/

  SC_HAS_PROCESS( rtl_to_tlm2_adaptor );

  rtl_to_tlm2_adaptor(sc_module_name _name) : sc_module(_name),
	                                          addr(0), data(0),
	                                          reset(false),
                                              r_nw(ZX),
											  cmd(tlm::TLM_IGNORE_COMMAND)
                                              { // Construct and name socket
  
    SC_THREAD(rttlm2_channel_thread);           // Register adaptor channel thread

	SC_METHOD(r_nw_method);                     // Register read/write method
		sensitive << R_NW;                          // Set sensitivity
		dont_initialize();                          // Inhibit method initialization
	
	trans = new tlm::tlm_generic_payload;       // Create new payload instance

  }

  private:

  /** SystemC phase callback **/

  void end_of_elaboration() {

	  OR_N->write(SC_LOGIC_1);
	  EOW_N->write(SC_LOGIC_1);

  }

  /** Variables **/

  unsigned short data;                          // Internal data buffer
  uint64 addr;                                  // Address word variable, used to interface between uint and sc_lv

  bool reset;                                   // Reset parameter
  
  sc_event rwe;                                 // Read/write enable event

  enum cmd_t {R, W, ZX} r_nw;                   // Read/write parameter

  tlm::tlm_generic_payload* trans;              // Generic payload instance
  tlm::tlm_command cmd;                         // TLM-2 generic payload transaction, reused across calls to b_transport

  /** Write thread **/

  void rttlm2_channel_thread() {

	  while(true) {

		if(RST_N->read() == SC_LOGIC_0) {       // Reset case

			if(!reset) {

				cmd = tlm::TLM_IGNORE_COMMAND;  // Hacked use of this command. Normally we need to setup our own

				addr = 0;                       // Set 'null' addr

				data = 0;                       // Write 0 to all cases

				cout << sc_time_stamp() << " ADAPTOR: Reseting" << endl;

				payload_setup(trans, cmd, data, addr);                    // Payload setup

				rtt2a_socket->b_transport(*trans, sc_time(SC_ZERO_TIME)); // Blocking transport call

				// Initiator obliged to check response status and delay
				if (trans->is_response_error())
					SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

				reset = true;                   // Update reset variable

				wait(MEM_PROCESS_TIME, MEM_TIME_UNIT);                    // Wait for the specified time

			}

		}

		else {

			switch(r_nw) {

				case W: {

					wait(CLK.posedge_event());  // Synchronous wait
					
					cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'W' << endl;

					cmd = tlm::TLM_WRITE_COMMAND;                             // Set command

					payload_setup(trans, cmd, data, addr);                    // Payload setup
		
					rtt2a_socket->b_transport(*trans, sc_time(SC_ZERO_TIME)); // Blocking transport call

					// Initiator obliged to check response status and delay
					if (trans->is_response_error())
						SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

					//cout << sc_time_stamp() << " ADAPTOR: Data written: " << d_word_t(data) << " " << data << endl;

					wait(MEM_PROCESS_TIME, MEM_TIME_UNIT);                    // Wait for the specified time

					eow_notify();                                             // Notify the end of write

					r_nw = ZX;                                                // Invalidate read/write variable

					break;

				}

				case R: {

					cout << sc_time_stamp() << " ADAPTOR: Command received: " << 'R' << endl;

					cmd = tlm::TLM_READ_COMMAND;                              // Set command

					payload_setup(trans, cmd, data, addr);                    // Payload setup
		
					rtt2a_socket->b_transport(*trans, sc_time(SC_ZERO_TIME)); // Blocking transport call

					// Initiator obliged to check response status and delay
					if (trans->is_response_error())
						SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

					wait(MEM_PROCESS_TIME, MEM_TIME_UNIT);                    // Wait for the specified time

					write(data);                                              // Write data back to port
					
					//cout << sc_time_stamp() << " ADAPTOR: Data read: " << d_word_t(data) << " " << data << endl;

					r_nw = ZX;                                                // Invalidate read/write variable

					break;

				}

				default: {
				    
					cout << sc_time_stamp() << " ADAPTOR: Wait for read/write event " << endl;

					wait(rwe);                  // Wait for the read/write enabled variable
					
					cout << sc_time_stamp() << " ADAPTOR: Read/write event triggered " << endl;

					addr = ADDR->read().to_uint64();    // Set addr

					data = DATA->read().to_uint();      // Set data <- Triggering 4-value warning

					cout << sc_time_stamp() << " ADAPTOR: Data received: " << DATA->read().to_string() << " " << data << endl;

				}
			}
			
			reset = false;                      // Deassert reset variable

			data = 0;                           // Flush data variable

		}

	  }

  }

  /** Read/write method **/

  void r_nw_method() {
	
	sc_logic tmp;                               // Temporary var

	tmp = R_NW->read();                         // Read read/write value from port
	
	if(tmp == SC_LOGIC_1) {                     // In case of high value, it is a write command
		r_nw = W;
        rwe.notify(SC_ZERO_TIME);               // Set read/write enable variable
    }
	else if(tmp == SC_LOGIC_0) {                // Else, it is a read command
		r_nw = R;
        rwe.notify(SC_ZERO_TIME);               // Set read/write enable variable
    }
	else                                        // If the read/write line is not 1 or 0, then mark it as
		r_nw = ZX;                              //  don't care

	cout << sc_time_stamp() << " ADAPTOR: Read/write method triggered " << endl;

	next_trigger(R_NW->default_event());        // Set next trigger

  }

  /** Methods **/

  // Sets up payload
  void payload_setup(tlm::tlm_generic_payload* trans,
	                 tlm::tlm_command cmd,
					 unsigned short& data,
					 unsigned int addr)
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

  // Write function that drives the data line properly, in order to avoid unresolved cases
  void write(unsigned short data) {

	  DATA->write(d_word_t(0));                  // Set line at 0

	  wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT); // Setup wait before writing

	  DATA->write(d_word_t(data));               // Write data on line

	  OR_N->write(SC_LOGIC_0);                   // Write output ready low (active state)

	  wait(MEM_HOLD_WRITE_TIME, MEM_TIME_UNIT);  // Hold wait
	  
	  DATA->write(d_word_t(0));                  // Set line at 0

	  OR_N->write(SC_LOGIC_1);                   // Write output ready high (inactive state)

	  wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT); // Post-hold wait

	  DATA->write(d_word_t('z'));                // Return line to high impedance

  }
  
  // Notify function that drives the EOW line
  void eow_notify() {

	  wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT); // Wait before signal writing

	  EOW_N->write(SC_LOGIC_0);                  // Signal the end of write

	  wait(MEM_HOLD_WRITE_TIME, MEM_TIME_UNIT);  // Signal hold wait

      EOW_N->write(SC_LOGIC_1);                  // Deassert the signal

	  wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT); // Wait after deasserting

  }
};

#endif
