/**
 * Memory IP testbench
 */

#include <systemc.h>
#include "../module/memory.h"

int main() {

	/** Signals **/

	sc_clock _clk("_clk", 10, SC_NS);
	sc_signal<sc_logic> _rst_n, _r_nw;
	sc_signal< a_word_t > _addr;
	sc_signal< d_word_t > _data;

	/** Memory instance **/

	memory mem0("mem0");

	/** Port binding **/

	mem0.CLK(_clk);
	mem0.RST_N(_rst_n);
	mem0.ADDR(_addr);
	mem0.DATA(_data);
	mem0.R_NW(_r_nw);

	/** Tracefile **/

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_mem");
	sc_write_comment(tf, "Memory simulation");
	tf->set_time_unit(1, SC_NS);

	sc_trace(tf,_clk,"_clk");
	sc_trace(tf,_rst_n,"_rst_n");
	sc_trace(tf,_addr,"_addr");
	sc_trace(tf,_data,"_data");
	sc_trace(tf,_r_nw,"_r_nw");

	/** Stimulus setting and simulation **/

	_rst_n.write(SC_LOGIC_0);

	sc_start(100, SC_NS);
	
	_rst_n.write(SC_LOGIC_1);
	_addr.write("0000000000000100");
	_data.write("1101001111000101");
	_r_nw.write(SC_LOGIC_1);

	sc_start(100, SC_US);

	_rst_n.write(SC_LOGIC_1);
	_addr.write("0000000000000101");
	_data.write("1101111111111111");
	_r_nw.write(SC_LOGIC_1);

	sc_start(100, SC_US);

	_rst_n.write(SC_LOGIC_1);
	_addr.write("0000000000000101");
	_data.write("1111111111111111");
	_r_nw.write(SC_LOGIC_0);

	sc_start(100, SC_US);

	_rst_n.write(SC_LOGIC_0);

	sc_start(100, SC_US);

	sc_close_vcd_trace_file(tf);

	return 0;

}
