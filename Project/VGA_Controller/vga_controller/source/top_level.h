#ifndef TOP_LEVEL_H
#define TOP_LEVEL_H

#include "vga_controller.h"
#include "sys_memory.h"

/**
 * Top-level Entity
 */

SC_MODULE( top_level ) {

	/** Top-level attributes **/
	vga_controller* vga_cont; // VGA Controller instance
	Memory* sys_mem;          // System memory instance
	sc_signal< sc_lv<10> > _t_r, _t_g, _t_b;              // Digital output signals for each channels
	sc_signal<sc_logic> _t_vga_clk, _t_vga_hs, _t_vga_vs; // Digital output signals for synchronisation
	sc_trace_file *tf;

	/** Top-level constructors **/
	SC_CTOR( top_level ) {

		sys_mem = new Memory("sys_mem0");
		vga_cont = new vga_controller("vga_cont0", 160, 120);

		/** Port connections **/
		vga_cont->vga_r(_t_r);
		vga_cont->vga_g(_t_g);
		vga_cont->vga_b(_t_b);
		vga_cont->vga_clk(_t_vga_clk);
		vga_cont->vga_hs(_t_vga_hs);
		vga_cont->vga_vs(_t_vga_vs);

		vga_cont->vga_socket.bind(sys_mem->socket);

		tf = sc_create_vcd_trace_file("wave_vga");
		sc_write_comment(tf, "VGA Controller simulation");
		tf->set_time_unit(1, SC_US);

		sc_trace(tf,_t_r,"r");
		sc_trace(tf,_t_g,"g");
		sc_trace(tf,_t_b,"b");
		sc_trace(tf,_t_vga_clk,"vga_clk");
		sc_trace(tf,_t_vga_hs,"hsync");
		sc_trace(tf,_t_vga_vs,"vsync");

	}

	~top_level() { sc_close_vcd_trace_file(tf); }

};

#endif
