/**
 * Memory IP testbench
 */

#include "../module/c/memory.h"
#include "../module/c/test_mod/mem_constraint.h"
#include <time.h>

#define N_TEST_RUN 4096

int main() {

	scv_random::set_global_seed(time(NULL));  // Random generator seeding

	/** Constants **/

	sc_time cycle_time = sc_time(SYS_CLOCK, SYS_CLOCK_UNIT); // Corresponds to a frequency of 100 MHz

	/** Signals **/

	sc_clock _clk("_clk", cycle_time);        // Clock instance
	sc_signal<bool> _rst_n, _r_nw;            // Bool signals for reset and read/write
	sc_signal< a_word_t > _addr;              // Address bus
	sc_signal< d_word_t > _datain, _dataout;  // Data buses

	/** Constraint module instance **/

	mem_constr_module mem_cm0("mem_cm0", N_TEST_RUN); // Create a new constraint module

	/** Memory instance **/

	memory mem0("mem0");                      // Create a new memory module

	/** Port binding **/

	mem0.CLK(_clk);
	mem0.RST_N(_rst_n);
	mem0.R_NW(_r_nw);
	mem0.ADDR(_addr);
	mem0.DATAIN(_datain);
	mem0.DATAOUT(_dataout);
	
	mem_cm0.CLK(_clk);
	mem_cm0.RST_N(_rst_n);
	mem_cm0.R_NW(_r_nw);
	mem_cm0.ADDR(_addr);
	mem_cm0.DATAIN(_dataout);
	mem_cm0.DATAOUT(_datain);

	/** Tracefile **/

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_mem");
	sc_write_comment(tf, "Memory simulation");
	tf->set_time_unit(1, SC_PS);

	sc_trace(tf,_clk,"_clk");
	sc_trace(tf,_rst_n,"_rst_n");
	sc_trace(tf,_r_nw,"_r_nw");
	sc_trace(tf,_addr,"_addr");
	sc_trace(tf,_datain,"_datain");
	sc_trace(tf,_dataout,"_dataout");

	/** Stimulus setting and simulation **/

	mem_cm0.disable_rst_randomization(true, true); // Disable reset, with initial value at 1

	sc_start((N_TEST_RUN+1)*(5), SC_NS);      // Start simulation
	
	sc_close_vcd_trace_file(tf);              // Close tracefile

	system("pause");                          // Pause

	return 0;

}
