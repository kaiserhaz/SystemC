#include "vga_controller.h"

/**
 * VGA Controller Module Implementation
 */

/** VGA Clock Divider Thread **/

void vga_controller::vga_clk_thread() {

	int _vga_clk_counter = 0;
	int _vga_clk_mult = (int)((_F_SYS_/_F_VGA_)+1.0);

	while(1) {

		wait(vga_controller::sys_clock.posedge_event());

		_vga_clk_counter += 1;

		if(_vga_clk_counter == _vga_clk_mult) {

			vga_controller::vga_clk_trig.notify();
			vga_controller::vga_clk->write(SC_LOGIC_1);

			_vga_clk_counter = 0;

			//cout << "VGA CONTROLLER: " << "VGA clock trigger" << endl;

		}
		else
			vga_controller::vga_clk->write(SC_LOGIC_0);

		//wait(vga_controller::sys_clock.posedge_event());

	}

}

/** VGA Controller Thread **/

void vga_controller::vga_cont_thread(){

	sc_lv<32> _vga_datain;
	sc_lv<10> _vga_r, _vga_g, _vga_b;
	int _vga_hsync=0, _vga_vsync=0;

	vga_controller::vga_hs->write(SC_LOGIC_1);
	vga_controller::vga_vs->write(SC_LOGIC_1);

	while(1) {

		wait(vga_controller::vga_clk_trig);

		_vga_hsync += 1;

		if(_vga_hsync == _X_FPOR_) {

			vga_controller::vga_hs->write(SC_LOGIC_0);

			//cout << "VGA CONTROLLER: " << "HSYNC triggered" << "@" << sc_time_stamp() << endl;

		}
		
		if(_vga_hsync == _X_FPOR_+_X_SYNC_) {

			vga_controller::vga_hs->write(SC_LOGIC_1);

			//cout << "VGA CONTROLLER: " << "HSYNC reseted" << endl;
		
		}

		if(_vga_hsync > _X_FPOR_+_X_SYNC_+_X_BPOR_) {

			_vga_datain = vga_controller::vga_datain->read();

			_vga_r = _vga_datain.range(0,9);
			_vga_g = _vga_datain.range(10,19);
			_vga_b = _vga_datain.range(20,29);

			vga_controller::vga_r->write(_vga_r);
			vga_controller::vga_g->write(_vga_g);
			vga_controller::vga_b->write(_vga_b);

		}

		if(_vga_hsync == vga_controller::_x_img_) {

			_vga_vsync += 1;
			_vga_hsync = 0;

		}

		if(_vga_vsync == _Y_FPOR_) {

			vga_controller::vga_vs->write(SC_LOGIC_0);

			//cout << "VGA CONTROLLER: " << "VSYNC triggered" << "@" << sc_time_stamp() << " vsync=" << _vga_vsync << endl;

		}
		
		if(_vga_vsync == _Y_FPOR_+_Y_SYNC_) {

			vga_controller::vga_vs->write(SC_LOGIC_1);

			//cout << "VGA CONTROLLER: " << "VSYNC reseted" << endl;

		}
		
		if(_vga_hsync == vga_controller::_x_img_)
			_vga_vsync = 0;

		//wait(vga_controller::vga_clk_trig);

	}

}
