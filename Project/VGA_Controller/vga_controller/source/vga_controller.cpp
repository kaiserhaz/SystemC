/**
 * @file vga_controller.cpp
 *
 * @brief VGA controller thread elaboration.
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

/**
 * VGA prefetch thread
 */
void vga_controller::vga_prefetch() {

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    tlm::tlm_command cmd = tlm::TLM_READ_COMMAND;
    sc_time delay = sc_time(5, SC_US);  // Let's say akin to DDR2-400B

    while(1)
    {

      trans->set_command( cmd );
      trans->set_address( vga_controller::f_i++ );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(vga_controller::curr_frame) );
      trans->set_data_length( 32 );     // Placeholder value, not really used in this example
      trans->set_streaming_width( 32 );
      trans->set_byte_enable_ptr( 0 );
      trans->set_dmi_allowed( false );
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

      // Call blocking transport
      vga_controller::vga_socket->b_transport( *trans, delay );

      // Check status of transaction
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      vga_controller::fetch_done = true;

      vga_controller::vga_done_trig.notify(SC_ZERO_TIME);

	  // Wait on the next fetch trigger
      wait(vga_controller::vga_fetch_trig);

	}

}

/**
 * VGA controller thread
 */
void vga_controller::vga_cont_thread() {

	cv::Vec3b _vga_datain;
	sc_bv<10> _vga_r, _vga_g, _vga_b;
	sc_time delay = sc_time(60, SC_NS); // Processing delay

	int _vga_hsync=0, _vga_vsync=0;
	int _ix = 0, _iy = 0;
	bool draw_img = false;
	
	vga_controller::vga_hs->write(true);
	vga_controller::vga_vs->write(true);

	while(vga_controller::f_i < 629) {  // TODO: Implement continuous display independent of frames

		if(!vga_controller::fetch_done) {

			wait(vga_controller::vga_done_trig); // Probably akin to something like a suspend mode during idle time
#ifdef _PRINT_DBG_
			cout << "VGA CONTROLLER: Fetch done" << endl;
#endif
			cout << "VGA CONTROLLER: Displaying frame #" << f_i << endl;

			cv::imshow("Current frame", *curr_frame);

			cv::waitKey(1);

		}

		_vga_hsync += 1;

		if(_vga_hsync == _X_FPOR_) {

			vga_controller::vga_hs->write(false);
#ifdef _PRINT_DBG_
			cout << "VGA CONTROLLER: " << "HSYNC triggered" << "@" << sc_time_stamp() << endl;
#endif
		}
		
		if(_vga_hsync == _X_FPOR_+_X_SYNC_) {

			vga_controller::vga_hs->write(true);
#ifdef _PRINT_DBG_
			cout << "VGA CONTROLLER: " << "HSYNC reseted" << endl;
#endif
		}

		if(_vga_hsync > _X_FPOR_+_X_SYNC_ && _vga_hsync <= _X_FPOR_+_X_SYNC_+vga_controller::x_res) {

			if(draw_img) {

				_vga_datain = vga_controller::curr_frame->at<cv::Vec3b>(_iy, _ix++);
#ifdef _PRINT_DBG_
				cout << "VGA CONTROLLER: Handling current pixel: " << " #" << _ix-1 << endl;
#endif
				_vga_r = vga_controller::ch2sc_bv<10>(_vga_datain[2]);
				_vga_g = vga_controller::ch2sc_bv<10>(_vga_datain[1]);
				_vga_b = vga_controller::ch2sc_bv<10>(_vga_datain[0]);

				vga_controller::vga_r->write(_vga_r);
				vga_controller::vga_g->write(_vga_g);
				vga_controller::vga_b->write(_vga_b);

			}

		}

		if(_vga_hsync == vga_controller::_x_img_) {

			_vga_vsync += 1;
			_ix = 0;
			_vga_hsync = 0;

			if(_vga_vsync == _Y_FPOR_) {

				vga_controller::vga_vs->write(false);
#ifdef _PRINT_DBG_
				cout << "VGA CONTROLLER: " << "VSYNC triggered" << "@" << sc_time_stamp()
				                                                << " vsync=" << _vga_vsync << endl;
#endif
			}
		
			if(_vga_vsync == _Y_FPOR_+_Y_SYNC_) {

				vga_controller::vga_vs->write(true);
#ifdef _PRINT_DBG_
				cout << "VGA CONTROLLER: " << "VSYNC reseted" << endl;
#endif
			}

			if(_vga_vsync > _Y_FPOR_+_Y_SYNC_ && _vga_vsync < _Y_FPOR_+_Y_SYNC_+vga_controller::y_res) {

				draw_img = true;

				_iy += 1;

			}
			else
				draw_img = false;
		
			if(_vga_vsync == vga_controller::_y_img_) {

				_iy = 0;
				_vga_vsync = 0;
				vga_controller::fetch_done = false;
				vga_controller::vga_fetch_trig.notify(SC_ZERO_TIME);

			}

		}

		wait(delay);

	}

	cout << "VGA CONTROLLER: No more frames to process" << endl;

	sc_stop();

}
