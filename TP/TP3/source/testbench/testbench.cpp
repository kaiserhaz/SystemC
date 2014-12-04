#include "testbench.h"

/**
 * Testbench module implementation
 */

testbench::testbench(sc_module_name name) {

	testbench::master_inst = new master("master_inst");
	testbench::slave_inst = new slave("slave_inst");
	testbench::tlm_bus_inst = new tlm_bus();

	master_inst->p_slave(*tlm_bus_inst);
	slave_inst->p_master(*tlm_bus_inst);

}
