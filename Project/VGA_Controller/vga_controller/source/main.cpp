/**
 * @file main.cpp
 *
 * @brief Main entry file for SystemC simulation.
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
 
 // Libs
#include "vga_controller.h"
#include "sys_memory.h"
#include "dac.h"

// Defs
#define _X_IMG_ 160                                         /**< Image width             */
#define _Y_IMG_ 120                                         /**< Image height            */

/**
 * SystemC entry point
 * @param argc Number of arguments passed onto the programme from command line
 * @param argv Names of arguments passed onto the programme from command line
 */
int sc_main(int argc, char *argv[]) {

	// System-level components
	vga_controller*                     vga_cont;           /**< VGA Controller instance */
	Memory*                             sys_mem;            /**< System memory instance  */
	dac*                                video_dac;          /**< Video DAC               */

	sys_mem = new Memory("sys_mem0");
	vga_cont = new vga_controller("vga_cont0", _X_IMG_, _Y_IMG_); // Specific to test-mpeg.mpg!
	video_dac = new dac("dac0");

	//Digital lines from controller to DAC, 10 bit
	sc_signal< sc_bv<10> >              _t_d_r,             /**< Red channel (digital)   */
	                                    _t_d_g,             /**< Green channel  (digital)*/
	                                    _t_d_b;             /**< Blue channel  (digital) */

	// Analog lines from DAC, 5V out at 8 bit depth
	sca_tdf::sca_signal<double>         _t_a_r,             /**< Red channel (analog)    */
	                                    _t_a_g,             /**< Green channel (analog)  */
	                                    _t_a_b;             /**< Blue channel (analog)   */

	// Digital lines for strobe synchronisation
	sc_signal<bool>                     _t_vga_hs,          /**< Horizontal sync (HSYNC) */
	                                    _t_vga_vs;          /**< Vertical sync (VSYNC)   */

	// Port connections
	vga_cont->vga_socket.bind(sys_mem->socket); // TLM2 socket bind

	// VGA controller port binds
	vga_cont->vga_r(_t_d_r);
	vga_cont->vga_g(_t_d_g);
	vga_cont->vga_b(_t_d_b);
	vga_cont->vga_hs(_t_vga_hs);
	vga_cont->vga_vs(_t_vga_vs);

	// DAC port binds
	video_dac->vga_r(_t_d_r);
	video_dac->vga_g(_t_d_g);
	video_dac->vga_b(_t_d_b);
	video_dac->dac_r(_t_a_r);
	video_dac->dac_g(_t_a_g);
	video_dac->dac_b(_t_a_b);

	// Output tracefile
#ifdef _TRACE_DBG_
	sca_trace_file *tf;
	tf = sca_create_vcd_trace_file("wave_vga");
	sca_write_comment(tf, "VGA Controller simulation");

	sca_trace(tf,_t_d_r,"d_r");
	sca_trace(tf,_t_d_g,"d_g");
	sca_trace(tf,_t_d_b,"d_b");
	sca_trace(tf,_t_a_r,"a_r");
	sca_trace(tf,_t_a_g,"a_g");
	sca_trace(tf,_t_a_b,"a_b");
	sca_trace(tf,_t_vga_hs,"hsync");
	sca_trace(tf,_t_vga_vs,"vsync");
#endif

	// Simulation start
	sc_start(/*20, SC_SEC*/);
#ifdef _TRACE_DBG_
	sca_close_vcd_trace_file(tf);
#endif
	system("sleep 1");

	return 0;

}
