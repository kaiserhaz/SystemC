#include "vga_controller.h"

/**
 * VGA Controller Module Implementation
 */

/** VGA Prefetch Thread **/

void vga_controller::vga_prefetch() {

	/** Edited copy from tlm_example1 **/
	// TLM-2 generic payload transaction, reused across calls to b_transport
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
	tlm::tlm_command cmd = tlm::TLM_READ_COMMAND;
    sc_time delay = sc_time(5, SC_US); // Let's say akin to DDR2-400B

    while(1)
    {

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      trans->set_command( cmd );
      trans->set_address( vga_controller::f_i++ );
	  trans->set_data_ptr( reinterpret_cast<unsigned char*>(vga_controller::curr_frame) );
      trans->set_data_length( 32 ); // Placeholder value, not really used in this example
      trans->set_streaming_width( 32 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      vga_controller::vga_socket->b_transport( *trans, delay );  // Blocking transport call

      // Initiator obliged to check response status and delay
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

	  vga_controller::fetch_done = true;

	  vga_controller::vga_done_trig.notify(SC_ZERO_TIME);

	  wait(vga_controller::vga_fetch_trig);

	}

}

/** VGA Controller Thread **/

void vga_controller::vga_cont_thread() {

	cv::Vec3b _vga_datain;
	sc_bv<10> _vga_r, _vga_g, _vga_b;
	sc_time delay = sc_time(60, SC_NS);
	int _vga_hsync=0, _vga_vsync=0;
	int _ix = 0, _iy = 0;
	bool draw_img = false;
	
	vga_controller::vga_hs->write(true);
	vga_controller::vga_vs->write(true);

	while(vga_controller::f_i < 10/*629*/) { // Hardcoded limit, only for that test-mpeg.mpg video!

		if(!vga_controller::fetch_done) {

			wait(vga_controller::vga_done_trig);
			
			//cout << "VGA CONTROLLER: Fetch done" << endl;

			cout << "VGA CONTROLLER: Displaying frame #" << f_i << endl;

			//cv::imshow("Current frame", *curr_frame);

			//cv::waitKey(1);

		}

		_vga_hsync += 1;

		if(_vga_hsync == _X_FPOR_) {

			vga_controller::vga_hs->write(false);

			//cout << "VGA CONTROLLER: " << "HSYNC triggered" << "@" << sc_time_stamp() << endl;

		}
		
		if(_vga_hsync == _X_FPOR_+_X_SYNC_) {

			vga_controller::vga_hs->write(true);

			//cout << "VGA CONTROLLER: " << "HSYNC reseted" << endl;
		
		}

		if(_vga_hsync > _X_FPOR_+_X_SYNC_ && _vga_hsync <= _X_FPOR_+_X_SYNC_+vga_controller::x_res) {

			if(draw_img) {

				_vga_datain = vga_controller::curr_frame->at<cv::Vec3b>(_iy, _ix++);

				//cout << "VGA CONTROLLER: Handling current pixel: " << " #" << _ix-1 << endl;

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

				//cout << "VGA CONTROLLER: " << "VSYNC triggered" << "@" << sc_time_stamp()
				//                                                << " vsync=" << _vga_vsync << endl;

			}
		
			if(_vga_vsync == _Y_FPOR_+_Y_SYNC_) {

				vga_controller::vga_vs->write(true);

				//cout << "VGA CONTROLLER: " << "VSYNC reseted" << endl;

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
