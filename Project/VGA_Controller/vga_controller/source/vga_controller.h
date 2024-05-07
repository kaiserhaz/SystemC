/**
 * @file vga_controller.h
 *
 * @brief VGA controller module.
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
#ifndef VGA_CONTROLLER_H
#define VGA_CONTROLLER_H

// Libs
#include "vga_controller_include.h"
// Hack for including both OpenCV and SystemC together
// The issue was highlighted below
// https://github.com/opencv/opencv/issues/7573
// In summary, it is because OpenCV defined the int64 and
//  uint64 datatypes in the global namespace, causing clash
//  with libraries that also define said types. However,
//  I think it should be compatible on the get-go since
//  SystemC implements int64 and uint64 in its own name-
//  space.
#define int64 cv_int64
#define uint64 cv_uint64
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#ifdef int64
#undef int64
#endif
#ifdef uint64
#undef uint64
#endif
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

/**
 * VGA controller module
 */
SC_MODULE(vga_controller) {

	// Attributes: ports
	sc_out< sc_bv<10> >                 vga_r,              /**< Red channel port    */
	                                    vga_g,              /**< Green channel port  */              
	                                    vga_b;              /**< Blue channel port   */
	sc_out<bool>                        vga_hs,             /**< Horizontal sync port*/
	                                    vga_vs;             /**< Vertical sync port  */
    tlm_utils::simple_initiator_socket<vga_controller>      vga_socket;         /**< TLM2 memory socket */

	// Thread declaration
	SC_HAS_PROCESS(vga_controller);

	// Constructor
	vga_controller() : sc_module("vga_cont_def0"),
	                   x_res(_X_MAX_)            ,
					   y_res(_Y_MAX_)            {

		init();

	}

	// Constructor: copy
	vga_controller(vga_controller &_vga_cont) : sc_module(_vga_cont.name())  ,
		                                        x_res(_vga_cont.get_x_res()) ,
												y_res(_vga_cont.get_y_res()) {

		init();

	}

	// Constructor: named
	vga_controller(sc_module_name _name) : sc_module(_name),
	                                       x_res(_X_MAX_)  ,
	                                       y_res(_Y_MAX_)  {

		init();

	}

	// Constructor: full
	vga_controller(sc_module_name _name, int _x_res, int _y_res) : sc_module(_name),
	                                                               x_res(_x_res)   ,
	                                                               y_res(_y_res)   {

		if((_x_res > _X_MAX_) || (_y_res > _Y_MAX_))
			SC_REPORT_ERROR("VGA Controller","Image resolution not supported");

		init();

	}

	// Destructor
	~vga_controller() { delete curr_frame; }

	// Attributes: methods
	int get_x_res() { return x_res; }
	int get_y_res() { return y_res; }

	private:

	// Attributes
	bool                                fetch_done;         /**< Fetch done indicator              */
	int                                 x_res;              /**< Image horizontal resolution       */
	int                                 y_res;              /**< Image vertical resolution         */
	int                                 _x_img_;            /**< Total image horizontal resolution */
	int                                 _y_img_;            /**< Total image vertical resolution   */
	unsigned int                        f_i;                /**< Frame index                       */
	cv::Mat*                            curr_frame;         /**< Current frame                     */
	sc_event                            vga_fetch_trig,     /**< VGA fetch event                   */
	                                    vga_done_trig;      /**< VGA fetch done event              */

	void                                vga_prefetch();     /**< VGA prefetch thread               */
	void                                vga_cont_thread();  /**< VGA controller thread             */

	/**
	 * VGA controller initialization thread
	 */
	void init() {

		// Calculate total image resolution that needs to be drawn
		_x_img_ = _X_SYNC_ + _X_FPOR_ + x_res + _X_BPOR_;
		_y_img_ = _Y_SYNC_ + _Y_FPOR_ + y_res + _Y_BPOR_;
#ifdef _PRINT_DBG_
		cout << "VGA_CONTROLLER: " << "Frame size is " << x_res << "x" << y_res << endl;
#endif
		curr_frame = new cv::Mat();

		f_i = 0;
		fetch_done = false;

		SC_THREAD(vga_prefetch);
			sensitive << vga_fetch_trig;
		SC_THREAD(vga_cont_thread);
			sensitive << vga_done_trig;

	}

	/**
	 * Convertor function to change `char` to `sc_bv`
	 */
	template<int T>
	sc_bv<T> ch2sc_bv(const unsigned char ch) {

		sc_bv<T> scbv;

		for(int i=0; i < scbv.length(); i++) // Lower index = lower power
			scbv[i] = (ch >> i) & 1;

		return scbv;

	}

};

#endif
