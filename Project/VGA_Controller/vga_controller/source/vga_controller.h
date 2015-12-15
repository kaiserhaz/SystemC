#ifndef VGA_CONTROLLER_H
#define VGA_CONTROLLER_H

#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "vga_controller_include.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

/**
 * VGA Controller Module
 */

SC_MODULE(vga_controller) {

	/** VGA Controller ports **/
	sc_out< sc_bv<10> > vga_r, vga_g, vga_b; // VGA dataout ports, separated into individual chromas
	sc_out<bool> vga_hs, vga_vs;             // VGA horizontal and vertical synchronization pulses
    tlm_utils::simple_initiator_socket<vga_controller> vga_socket; // TLM2 socket to connect to memory

	SC_HAS_PROCESS(vga_controller);

	/** VGA Controller constructors & destructor **/

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
			SC_REPORT_ERROR("VGA Controller","Image resolution not supported");

		init();

	}

	~vga_controller() { delete curr_frame; }

	/** VGA Controller methods **/

	int get_x_res() { return x_res; }
	int get_y_res() { return y_res; }

	private:

	/** VGA Controller attributes **/

	bool fetch_done;       // Fetch bit
	int x_res;             // Image horizontal resolution
	int y_res;             // Image vertical resolution
	int _x_img_;           // Total image horizontal resolution
	int _y_img_;           // Total image vertical resolution
	unsigned int f_i;      // Frame index
	cv::Mat* curr_frame;   // Current frame
	sc_event vga_fetch_trig, vga_done_trig; // VGA fetch and fetch done trigger event

	void init() {

		// Calculate total image resolution that needs to be drawn
		_x_img_ = _X_SYNC_ + _X_FPOR_ + x_res + _X_BPOR_;
		_y_img_ = _Y_SYNC_ + _Y_FPOR_ + y_res + _Y_BPOR_;

		//cout << "VGA_CONTROLLER: " << "Frame size is " << x_res << "x" << y_res << endl;

		curr_frame = new cv::Mat();

		f_i = 0;
		fetch_done = false;

		SC_THREAD(vga_prefetch);
			sensitive << vga_fetch_trig;
		SC_THREAD(vga_cont_thread);
			sensitive << vga_done_trig;

	}

	void vga_prefetch();
	void vga_cont_thread();
	template<int T>
	sc_bv<T> ch2sc_bv(const unsigned char ch) {

		sc_bv<T> scbv;

		for(int i=0; i < scbv.length(); i++) // Lower index = lower power
			scbv[i] = (ch >> i) & 1;

		return scbv;

	}

};

#endif
