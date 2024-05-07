/**
 * @file top_level.h (UNUSED)
 *
 * @brief Top-level entity combining VGA controller and memory.
 * 
 * -- Versioning Info --
 *
 * v0.0 : Before 07/05/2024 : Initial working config write-up.
 * v1.0 : 07/05/2024 : Edited for clarity.
 *
 * @copyright
 * Copyright 2024 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */

// Def guard
#ifndef TOP_LEVEL_H
#define TOP_LEVEL_H

// Libs
#include "vga_controller.h"
#include "sys_memory.h"

/**
 * Top-level entity
 */
SC_MODULE( top_level ) {

	// Attributes: modules
	vga_controller*                     vga_cont;           /**< VGA Controller instance */
	Memory*                             sys_mem;            /**< System memory instance  */
	
	// Attributes: signals
	sc_signal< sc_lv<10> >              _t_r,               /**< Red channel             */
	                                    _t_g,               /**< Green channel           */
	                                    _t_b;               /**< Blue channel            */
	sc_signal<sc_logic>                 _t_vga_clk,         /**< Clock                   */
	                                    _t_vga_hs,          /**< Horizontal sync (HSYNC) */
	                                    _t_vga_vs;          /**< Vertical sync (VSYNC)   */
	
	// Attributes: others
	sc_trace_file*                      tf;                 /**< Signal trace file       */

	// Constructor
	SC_CTOR( top_level ) {

		sys_mem = new Memory("sys_mem0");
		vga_cont = new vga_controller("vga_cont0", 160, 120);

		// Port bindings
		vga_cont->vga_r(_t_r);
		vga_cont->vga_g(_t_g);
		vga_cont->vga_b(_t_b);
		vga_cont->vga_clk(_t_vga_clk);
		vga_cont->vga_hs(_t_vga_hs);
		vga_cont->vga_vs(_t_vga_vs);

		vga_cont->vga_socket.bind(sys_mem->socket);
#ifdef _TRACE_DBG_
		tf = sc_create_vcd_trace_file("wave_vga");
		sc_write_comment(tf, "VGA Controller simulation");
		tf->set_time_unit(1, SC_US);

		sc_trace(tf,_t_r,"r");
		sc_trace(tf,_t_g,"g");
		sc_trace(tf,_t_b,"b");
		sc_trace(tf,_t_vga_clk,"vga_clk");
		sc_trace(tf,_t_vga_hs,"hsync");
		sc_trace(tf,_t_vga_vs,"vsync");
#endif
	}

	// Destructor
	~top_level() { sc_close_vcd_trace_file(tf); delete vga_cont; delete sys_mem; }

};

#endif
