/**
 * Main
 */

#include <time.h>
#include <systemc.h>
#include "vga_controller.h"

int sc_main(int argc, char *argv[]) {

	srand(time(NULL));

	vga_controller vga_cont0("vga_cont0", 80, 60);

	sc_signal< sc_lv<10> > _t_r, _t_g, _t_b;
	sc_signal< sc_lv<32> > _t_datain;
	sc_signal<sc_logic> _t_vga_clk, _t_vga_hs, _t_vga_vs;

	sc_clock sys_clk("sys_clk0", 15, SC_NS);

	sc_lv<32> __t_datain;

	/** Port connections **/

	vga_cont0.vga_datain(_t_datain);
	vga_cont0.sys_clock(sys_clk);
	vga_cont0.vga_r(_t_r);
	vga_cont0.vga_g(_t_g);
	vga_cont0.vga_b(_t_b);
	vga_cont0.vga_clk(_t_vga_clk);
	vga_cont0.vga_hs(_t_vga_hs);
	vga_cont0.vga_vs(_t_vga_vs);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_vga");
	sc_write_comment(tf, "VGA Controller simulation");
	tf->set_time_unit(1, SC_NS);

	//sc_trace(tf,sys_clk, "sys_clk");
	sc_trace(tf,_t_datain,"datain");
	sc_trace(tf,_t_r,"r");
	sc_trace(tf,_t_g,"g");
	sc_trace(tf,_t_b,"b");
	sc_trace(tf,_t_vga_clk,"vga_clk");
	sc_trace(tf,_t_vga_hs,"hsync");
	sc_trace(tf,_t_vga_vs,"vsync");

	int _i_max_ = (int)(_F_ * (_X_SYNC_ + _X_FPOR_ + vga_cont0.get_x_res() + _X_BPOR_) *
		                (_Y_SYNC_ + _Y_FPOR_ + vga_cont0.get_y_res() + _Y_BPOR_));

	for(int i=0; i<60; i++) {

		for(int j=0; j<30; j++)
			__t_datain[j] = rand() % 2;

		_t_datain = __t_datain;

		cout << "TESTBENCH: Tracing image #" << i << endl;

		sc_start(17, SC_MS);

	}

	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}
