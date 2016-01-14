/**
 * Memory IP testbench
 */

#include "../module/memory.h"
#include "../module/mem_constraint.h"
#include <time.h>

#define N_TEST_RUN 1000

int main() {

	scv_random::set_global_seed(time(NULL));                 // Random generator seeding

	/** Constants **/

	sc_time cycle_time = sc_time(SYS_CLOCK, SYS_CLOCK_UNIT); // Corresponds to a frequency of 100 MHz

	/** Signals **/

	sc_clock _clk("_clk", cycle_time);                       // Clock instance
	sc_signal<sc_logic> _rst_n, _r_nw, _or_n, _eow_n;        // sc_logic signals for reset and read/write
	sc_signal< a_word_t > _addr;                             // Address bus
	sc_signal_rv<MEM_DATA_WORD_LEN> _data;                   // Resolved data bus

	/** Constraint module instance **/

	mem_constr_module mem_cm0("mem_cm0", N_TEST_RUN);        // Create a new constraint module

	/** Memory instance **/

	memory mem0("mem0");                                     // Create a new memory module

	/** Port binding **/

	mem0.CLK(_clk);
	mem0.RST_N(_rst_n);
	mem0.R_NW(_r_nw);
	mem0.OR_N(_or_n);
	mem0.EOW_N(_eow_n);
	mem0.ADDR(_addr);
	mem0.DATA(_data);
	
	mem_cm0.RST_N(_rst_n);
	mem_cm0.R_NW(_r_nw);
	mem_cm0.OR_N(_or_n);
	mem_cm0.EOW_N(_eow_n);
	mem_cm0.ADDR(_addr);
	mem_cm0.DATA(_data);

	/** Tracefile **/

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_mem");
	sc_write_comment(tf, "Memory simulation");
	tf->set_time_unit(1, SC_NS);

	sc_trace(tf,_clk,"_clk");
	sc_trace(tf,_rst_n,"_rst_n");
	sc_trace(tf,_r_nw,"_r_nw");
	sc_trace(tf,_or_n,"_or_n");
	sc_trace(tf,_eow_n,"_eow_n");
	sc_trace(tf,_addr,"_addr");
	sc_trace(tf,_data,"_data");
	
	/** Stimulus setting and simulation **/

	mem_cm0.disable_rst_randomization(true, SC_LOGIC_1);     // Disable reset, with initial value at 1

	sc_start();                                              // Start simulation

	mem_cm0.disable_rst_randomization(true, SC_LOGIC_0);     // Disable reset, with initial value at 0

	//sc_start(10*cycle_time);                                 // Start simulation
	
	sc_close_vcd_trace_file(tf);                             // Close tracefile

	system("pause");                                         // Pause

	return 0;

}
