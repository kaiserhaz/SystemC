/**
 * Memory IP testbench
 */

#ifndef MEMORY_TESTBENCH_H
#define MEMORY_TESTBENCH_H

#include <systemc.h>
#include "..\vnc_inc.h"
#include "..\module\memory.h"

#define N_TEST_RUN 5000

SC_MODULE( memory_testbench ) {

	/** Constants **/

	sc_time cycle_time; // Corresponds to a frequency of 100 MHz

	/** Signals **/

	sc_clock _clk;
	sc_signal<sc_logic> _rst_n, _r_nw;
	sc_signal< a_word_t > _addr;
	sc_signal< d_word_t > _data;

	/** Constraint class **/

	mem_constraint* mem_c0;

	/** Memory instance **/

	memory* mem0;

	/** Tracefile **/

	sc_trace_file* tf;

	/** Testbench Constructor **/

	SC_CTOR( memory_testbench ) : _clk("_clk", cycle_time) {

		SC_THREAD( memory_testbench_thread );
		dont_initialize();

		scv_random::set_global_seed(0xFA13); // Random generator seeding

		cycle_time = sc_time(10, SC_NS);     // Corresponds to a frequency of 100 MHz

		mem0 = new memory("mem0", cycle_time); // Instantiating memory instance

		mem_c0 = new mem_constraint("mem_c0"); // Constraint class instantiation
		mem_c0->m_t0->rst_n.disable_randomization(); // Disable random resets
		mem_c0->m_t0->rst_n.write(SC_LOGIC_1);

		tf = sc_create_vcd_trace_file("wave_mem"); // Tracefile creation

	}

	~memory_testbench() { sc_close_vcd_trace_file(tf); }

	/** Thread process **/

	void memory_testbench_thread() {

		/** Port binding **/

		mem0->CLK(_clk);
		mem0->RST_N(_rst_n);
		mem0->ADDR(_addr);
		mem0->DATA(_data);
		mem0->R_NW(_r_nw);
	
		sc_write_comment(tf, "Memory simulation");
		tf->set_time_unit(1, SC_NS);

		sc_trace(tf,_clk,"_clk");
		sc_trace(tf,_rst_n,"_rst_n");
		sc_trace(tf,_addr,"_addr");
		sc_trace(tf,_data,"_data");
		sc_trace(tf,_r_nw,"_r_nw");

		/** Stimulus setting and simulation **/

		_rst_n.write(SC_LOGIC_0);
		_r_nw.write(SC_LOGIC_0);

		sc_start(100, SC_NS);

		_rst_n.write(SC_LOGIC_1);
	
		for(int ii=0; ii < N_TEST_RUN; ii++) {

			mem_c0->m_t0->next();

			cout << sc_time_stamp() << " TESTBENCH: Transaction value:\n" << *mem_c0->m_t0->get_instance() << endl;

			_rst_n.write(mem_c0->m_t0->rst_n.read());
			_r_nw.write(mem_c0->m_t0->r_nw.read());
			_addr.write(mem_c0->m_t0->addr.read());

			if(_r_nw == SC_LOGIC_1)
				_data.write(mem_c0->m_t0->data.read());

			wait(_data.value_changed_event());

			if(_r_nw == SC_LOGIC_0)
				cout << sc_time_stamp() << " TESTBENCH: Value read: " << _data << endl;

			cout << endl;

		}

	}

};

#endif
