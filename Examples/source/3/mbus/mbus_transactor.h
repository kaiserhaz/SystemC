/**
 * 3.2.2 : MBus Transactor
 */

/**
 * Define guard
 */
#ifndef MBUS_TRANSACTOR_H
#define MBUS_TRANSACTOR_H

/**
 * Includes
 */
#include <systemc.h>
#include "mbus.h"
#include "mbus_memory.h"

/**
 * MBus Transactor Module
 */
SC_MODULE( mbus_transactor ) {

	/** MBus Transactor Ports **/
	sc_in<mbus> trans_bus_;

	/** MBus Transactor Submodules **/
	mbus_memory* mbus_mem_inst0_;

	/** MBus Transactor Internal Signals **/
	sc_signal<bool> trans_rw_;
	sc_signal< sc_uint<ADDR_WIDTH> > trans_addr_;
	sc_signal< sc_uint<DATA_WIDTH> > trans_data_in_, trans_data_out_;

	/** MBus Transactor Contructor **/
	SC_CTOR( mbus_transactor );

	/** MBus Transactor Routines **/
	void trans_thread_(void);

	/** MBus Transactor Methods **/
	void trans_read_(void);
	void trans_write_(void);

};

#endif
