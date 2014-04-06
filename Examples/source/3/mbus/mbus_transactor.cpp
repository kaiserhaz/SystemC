/**
 * 3.2.3 : MBus Transactor Implementation
 */

/**
 * Includes
 */
#include <systemc.h>
#include "mbus_transactor.h"

/**
 * MBus Transactor Implementation
 */

/** Constructor **/
mbus_transactor::mbus_transactor(sc_module_name __name_) : sc_module(__name_), trans_bus_("trans_bus") {

	// Submodules intansciation
	mbus_mem_inst0_ = new mbus_memory("mbus_mem_inst0", ADDR_WIDTH);
		mbus_mem_inst0_->mbus_rw_(trans_rw_);
		mbus_mem_inst0_->mbus_addr_(trans_addr_);
		mbus_mem_inst0_->mbus_data_in_(trans_data_in_);
		mbus_mem_inst0_->mbus_data_out_(trans_data_out_);

	// Thread declaration
	SC_THREAD( trans_thread_ );

}

/** Threads **/

/** void trans_thread_ ( void ) : Main thread for the transactor **/
void mbus_transactor::trans_thread_(void) {

	// Protect and disprotect bus conditions
	mbus PROTECT_BUS, DISPROTECT_BUS;

	// Sticky protect bit
	bool protect;

	PROTECT_BUS.address = (sc_uint<ADDR_WIDTH>) 0x0;
	PROTECT_BUS.data    = (sc_uint<DATA_WIDTH>) 0xF0;
	PROTECT_BUS.read    = false;
	PROTECT_BUS.write   = true;

	DISPROTECT_BUS.address = (sc_uint<ADDR_WIDTH>) 0x0;
	DISPROTECT_BUS.data    = (sc_uint<DATA_WIDTH>) 0xF1;
	DISPROTECT_BUS.read    = false;
	DISPROTECT_BUS.write   = true;

	protect = true;

	// Main loop
	while(true) {

		// Wait for transaction (wait on default event (or value-change event))
		wait( trans_bus_->default_event() );

		// Test protect bit
		if( protect ) {

			// If the disprotect condition is satisfied, disprotect the RW from/to memory
			if( trans_bus_->read() == DISPROTECT_BUS ) {

				// Reset protect bit
				protect = false;

				cout << " Memory disprotected " << endl;

			}

			// Else, ignore
			else {

				cout << " Memory protected " << endl;

			}

		}

		// If protect bit is reset
		else {

			// If the protect condition is satisfied, set the protect bit
			if( trans_bus_->read() == PROTECT_BUS ) {
				
				// Set protect bit
				protect = true;

			}

			// Test the read signal for read
			else if( trans_bus_->read().read == true ) {

				// Initiate read
				trans_read_();

			}

			// If not read, then it is write
			else if ( trans_bus_->read().write == true ) {

				// Initiate write
				trans_write_();

			}

			// Else it is considered a transaction error
			else {

				cout << " Transaction error " << endl;

			}

		}

	}

}

/** Methods **/

/** void trans_read( void ) : Initiates a read **/
void mbus_transactor::trans_read_(void) {

	trans_rw_.write(false);                        // Reset RW line to false for read
	trans_addr_.write(trans_bus_->read().address); // Write received address to memory

}

/** void trans_write() : Initiates a write **/
void mbus_transactor::trans_write_(void) {

	trans_rw_.write(true);                         // Set RW line to true for write
	trans_addr_.write(trans_bus_->read().address); // Write received address to memory
	trans_data_in_.write(trans_bus_->read().data); // Write received data to memory

}
