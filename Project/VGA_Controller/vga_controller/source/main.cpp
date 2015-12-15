/**
 * Main
 */

#include "vga_controller.h"
#include "sys_memory.h"
#include "dac.h"

int sc_main(int argc, char *argv[]) {

	vga_controller* vga_cont; // VGA Controller instance
	Memory* sys_mem;          // System memory instance
	dac* video_dac;           // Video DAC

	sc_signal< sc_bv<10> > _t_d_r, _t_d_g, _t_d_b;      // Digital output from VGA controller to DAC
	sca_tdf::sca_signal<double> _t_a_r, _t_a_g, _t_a_b; // Analog output from DAC
	sc_signal<bool> _t_vga_hs, _t_vga_vs;               // Digital output signals for synchronisation
	
	sca_trace_file *tf;

	sys_mem = new Memory("sys_mem0");
	vga_cont = new vga_controller("vga_cont0", 160, 120); // Specific to test-mpeg.mpg!
	video_dac = new dac("dac0");

	/** Port connections **/

	vga_cont->vga_socket.bind(sys_mem->socket); // TLM2 socket bind

	// VGA controller binds
	vga_cont->vga_r(_t_d_r);
	vga_cont->vga_g(_t_d_g);
	vga_cont->vga_b(_t_d_b);
	vga_cont->vga_hs(_t_vga_hs);
	vga_cont->vga_vs(_t_vga_vs);

	// DAC binds
	video_dac->vga_r(_t_d_r);
	video_dac->vga_g(_t_d_g);
	video_dac->vga_b(_t_d_b);
	video_dac->dac_r(_t_a_r);
	video_dac->dac_g(_t_a_g);
	video_dac->dac_b(_t_a_b);

	//tf = sca_create_vcd_trace_file("wave_vga");
	//sca_write_comment(tf, "VGA Controller simulation");

	//sca_trace(tf,_t_d_r,"d_r");
	//sca_trace(tf,_t_d_g,"d_g");
	//sca_trace(tf,_t_d_b,"d_b");
	//sca_trace(tf,_t_a_r,"a_r");
	//sca_trace(tf,_t_a_g,"a_g");
	//sca_trace(tf,_t_a_b,"a_b");
	//sca_trace(tf,_t_vga_hs,"hsync");
	//sca_trace(tf,_t_vga_vs,"vsync");

	sc_start(/*20, SC_SEC*/);

	//sca_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
