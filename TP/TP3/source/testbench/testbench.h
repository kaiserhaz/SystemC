#include "../module/master/master.h"
#include "../module/slave/slave.h"
#include "../bus/tlm_bus.h"

/**
 * Testbench module
 */

SC_MODULE( testbench ) {

	master* master_inst;
	slave* slave_inst;
	tlm_bus* tlm_bus_inst;

	SC_HAS_PROCESS( testbench );

	testbench(sc_module_name name);

};
