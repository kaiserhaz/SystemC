/**
 * 3.2.6 : MBus Example Simulation and Trace
 */

/**
 * Includes
 */
#include <systemc.h>
#include "mbus.h"
#include "mbus_transactor.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Elaboration phase
	//
	//

	// Set simulation time resolution
	sc_set_time_resolution(1, SC_US);

	// MBus instance
	sc_signal<mbus> test_bus;

	// MBus transactions
	mbus trans_r_violate,
		 trans_w_violate,
		 trans_unprotect,
		 trans_err,
		 trans_protect;

	mbus *trans_w_mem, *trans_r_mem;

	trans_r_violate.address = 0x1;
	trans_r_violate.data    = 0x00;
	trans_r_violate.read    = true;
	trans_r_violate.write   = false;

	trans_w_violate.address = 0x1;
	trans_w_violate.data    = 0x00;
	trans_w_violate.read    = false;
	trans_w_violate.write   = true;

	trans_unprotect.address = 0x0;
	trans_unprotect.data    = 0xF1;
	trans_unprotect.read    = false;
	trans_unprotect.write   = true;

	trans_err.address = 0x1;
	trans_err.data    = 0x00;
	trans_err.read    = false;
	trans_err.write   = false;

	trans_protect.address = 0x0;
	trans_protect.data    = 0xF0;
	trans_protect.read    = false;
	trans_protect.write   = true;

	int i, sz;

	sz = 1;

	for(i=0; i<ADDR_WIDTH; i++) {

		sz *= 2;

	}

	trans_r_mem = new mbus[sz];
	trans_w_mem = new mbus[sz];

	for(i=0; i<sz; i++) {

		trans_r_mem[i].address = (sc_uint<ADDR_WIDTH>)i;
		trans_r_mem[i].data = 0x00;
		trans_r_mem[i].read = true;
		trans_r_mem[i].write = false;

		trans_w_mem[i].address = (sc_uint<ADDR_WIDTH>)i;
		trans_w_mem[i].data = (sc_uint<DATA_WIDTH>)i;
		trans_w_mem[i].read = false;
		trans_w_mem[i].write = true;

	}

	// MBus transactor instance
	mbus_transactor test_trans0("test_trans0");
		test_trans0.trans_bus_(test_bus);

	// Tracefile setup
	sc_trace_file *tf = sc_create_vcd_trace_file("wave_mbus_trans");
	sc_write_comment(tf, "Simulation of MBus Transaction");
	tf->set_time_unit(1, SC_US);

	sc_trace(tf, test_bus, "test_bus");

	// Simulation phase
	//
	//

	// Start simulation
	sc_start(5, SC_US);

	test_bus.write(trans_r_violate);
	sc_start(3, SC_US);

	test_bus.write(trans_w_violate);
	sc_start(2, SC_US);

	test_bus.write(trans_unprotect);
	sc_start(10, SC_US);

	for(i=0; i<sz; i++) {
		
		test_bus.write(trans_w_mem[i]);
		sc_start(2, SC_US);

	}

	for(i=0; i<sz; i++) {
		
		test_bus.write(trans_r_mem[i]);
		sc_start(2, SC_US);

	}

	test_bus.write(trans_err);
	sc_start(10, SC_US);

	test_bus.write(trans_protect);
	sc_start(5, SC_US);

	// Free memory
	delete[] trans_w_mem;
	delete[] trans_r_mem;

	// Close tracefile
	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
