/**
 * Von Neumann Calculator Testbench elaboration
 */

#include "test_four_bit_counter.h"

SC_MODULE_EXPORT(cpu_testbench);               // ModelSim proprietary function

/** Clock driver **/
void cpu_testbench::clock_assign1(void) {
		
	if(sys_clk0.posedge())
		t_clk.write('1');
	else
		t_clk.write('0');
	
//	next_trigger(sys_clk0.default_event());
	
}

/** Bus clock driver **/
void cpu_testbench::clock_assign2(void) {
		
	if(bus_clk0.posedge())
		t_clkbus.write('1');
	else
		t_clkbus.write('0');
	
//	next_trigger(bus_clk0.default_event());
	
}

/** Main scenario testbench **/
void cpu_testbench::test_bench(void) {
	
	cout << " Resetting " << endl;
	
	
		
	cout << " Stop reset and start " << endl;

	
		
	cout << " Change direction " << endl;
		
	
		
	cout << " Data load " << endl;

	
	
	cout << " Write high " << endl;
	
	
	
	cout << " Write low " << endl;
	
	
		
	cout << " Resetting " << endl;

	
	
}
