/**
 * 3.2.4 : MBus Memory
 */

/**
 * Define guard
 */
#ifndef MBUS_MEMORY_H
#define MBUS_MEMORY_H

/**
 * Includes
 */
#include <systemc.h>
#include "mbus.h"

/**
 * MBus Transactor Module
 */
SC_MODULE( mbus_memory ) {

	/** MBus Memory ports **/
	sc_in<bool> mbus_rw_;
	sc_in< sc_uint<ADDR_WIDTH> > mbus_addr_;
	sc_in< sc_uint<DATA_WIDTH> > mbus_data_in_;
	sc_out< sc_uint<DATA_WIDTH> > mbus_data_out_;

	/** MBus Memory cases **/
	sc_uint<DATA_WIDTH>* mbus_mem_case_;

	/** MBus Memory Contructor **/
	SC_HAS_PROCESS( mbus_memory );

	mbus_memory(sc_module_name __name_, int __size_);

	/** MBus Memory Destructor **/
	~mbus_memory();

	/** MBus Memory Routines **/
	void mbus_mem_thread_(void);

	/** MBus Memory Methods **/
	void mbus_mem_write_(const sc_uint<ADDR_WIDTH>& __addr_, const sc_uint<DATA_WIDTH>& __data_);
	sc_uint<DATA_WIDTH> mbus_mem_read_(const sc_uint<ADDR_WIDTH>& __addr_);

};

#endif
