/**
 * 3.2.5 : MBus Memory Implementation
 */

/**
 * Includes
 */
#include <systemc.h>
#include "mbus_memory.h"

/**
 * MBus Memory Implementation
 */

/** Constructor **/
mbus_memory::mbus_memory(sc_module_name __name_, int __size_) : sc_module(__name_) {

	// Allocate memory cases
	int i, sz;

	sz = 1;

	for(i=0; i<__size_; i++) {

		sz *= 2;

	}

	mbus_mem_case_ = new sc_uint<DATA_WIDTH>[sz];

	// Thread declaration
	SC_THREAD( mbus_mem_thread_ );

}

/** Destructor **/
mbus_memory::~mbus_memory() { delete[] mbus_mem_case_; }

/** Threads **/

/** mbus_mem_thread_ ( void ) : Main thread for the memory **/
void mbus_memory::mbus_mem_thread_(void) {

	// Main loop
	while( true ) {

		// Wait on changes in address or data
		wait( mbus_addr_->default_event() | mbus_data_in_->default_event() );

		// If the RW line is true, then it is a write
		if( mbus_rw_->read() == true ) {

			// Writes to memory
			mbus_mem_write_(mbus_addr_->read(), mbus_data_in_->read());

		}

		// Else, it is a read
		else {

			// Reads from memory
			mbus_data_out_->write(mbus_mem_read_(mbus_addr_->read()));

		}

	}

}

/** Methods **/

/** void mbus_mem_write_(const sc_uint<ADDR_WIDTH>& __addr_, const sc_uint<DATA_WIDTH>& __data_) : Writes data in memory **/
void mbus_memory::mbus_mem_write_(const sc_uint<ADDR_WIDTH>& __addr_, const sc_uint<DATA_WIDTH>& __data_) {

	mbus_mem_case_[__addr_.to_int()] = __data_;

	cout << " Value " << __data_ << " written to case #" << __addr_.to_int() << endl;

}

/** sc_uint<DATA_WIDTH> mbus_mem_read_(const sc_uint<ADDR_WIDTH>& __addr_) : Reads data from memory **/
sc_uint<DATA_WIDTH> mbus_memory::mbus_mem_read_(const sc_uint<ADDR_WIDTH>& __addr_) {

	cout << " Value " << mbus_mem_case_[__addr_.to_int()] << " read from case #" << __addr_.to_int() << endl;

	return mbus_mem_case_[__addr_.to_int()];

}
