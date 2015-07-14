#ifndef VGA_CONTROLLER_H
#define VGA_CONTROLLER_H

#include <systemc.h>
#include "vga_controller_include.h"

/**
 * VGA Controller Module
 */

SC_MODULE(vga_controller) {

	/** VGA Controller attributes **/
	int x_res;
	int y_res;
	int _x_img_;
	int _y_img_;
	sc_event vga_clk_trig;

	/** VGA Controller ports **/
	sc_in<bool> sys_clock;
	sc_in<sc_lv<32>> vga_datain;
	sc_out<sc_lv<10>> vga_r, vga_g, vga_b;
	sc_out<sc_logic> vga_clk;
	sc_out<sc_logic> vga_hs, vga_vs;

	SC_HAS_PROCESS(vga_controller);

	/** VGA Controller constructors **/

	vga_controller() : sc_module("vga_cont_def0"), x_res(_X_MAX_), y_res(_Y_MAX_) {

		init();

	}

	vga_controller(vga_controller &_vga_cont) : sc_module(_vga_cont.name()),
		                                        x_res(_vga_cont.get_x_res()),
												y_res(_vga_cont.get_y_res()) {

		init();

	}

	vga_controller(sc_module_name _name) : sc_module(_name), x_res(_X_MAX_), y_res(_Y_MAX_) {

		init();

	}

	vga_controller(sc_module_name _name, int _x_res, int _y_res) : sc_module(_name), x_res(_x_res), y_res(_y_res) {

		if((_x_res > _X_MAX_) || (_y_res > _Y_MAX_))
			SC_REPORT_ERROR("","Image resolution not supported");

		init();

	}

	/** VGA Controller methods **/

	int get_x_res() { return x_res; }
	int get_y_res() { return y_res; }

	void init() {

		_x_img_ = _X_SYNC_ + _X_FPOR_ + x_res + _X_BPOR_;
		_y_img_ = _Y_SYNC_ + _Y_FPOR_ + y_res + _Y_BPOR_;

		cout << "VGA_CONTROLLER: " << "Image size is " << x_res << "x" << y_res << endl;

		SC_THREAD(vga_clk_thread);
			sensitive << sys_clock;
		SC_THREAD(vga_cont_thread);
			sensitive << vga_clk_trig;

	}

	void vga_clk_thread();
	void vga_cont_thread();

};

#endif
