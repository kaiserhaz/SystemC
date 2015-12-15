#ifndef DAC_H
#define DAC_H

#include <systemc-ams.h>

#define _V_MAX_ 5.0
#define _IMG_DEPTH_ 255.0

/**
 * Digital-to-Analog Converter Module
 */

SCA_TDF_MODULE( dac ) {

	sca_tdf::sca_de::sca_in< sc_bv<10> > vga_r;
	sca_tdf::sca_de::sca_in< sc_bv<10> > vga_g;
	sca_tdf::sca_de::sca_in< sc_bv<10> > vga_b;

	sca_tdf::sca_out<double> dac_r;
	sca_tdf::sca_out<double> dac_g;
	sca_tdf::sca_out<double> dac_b;
	
	SCA_CTOR( dac ) {}

	private:

	void set_attributes() {

		dac_r.set_timestep(5, SC_NS); // 50 Msps is minimum rate, 20 ns
		dac_g.set_timestep(5, SC_NS);
		dac_b.set_timestep(5, SC_NS);

	}

	void processing() {

		dac_r.write(_V_MAX_ * (vga_r.read().to_ulong()/_IMG_DEPTH_));
		dac_g.write(_V_MAX_ * (vga_g.read().to_ulong()/_IMG_DEPTH_));
		dac_b.write(_V_MAX_ * (vga_b.read().to_ulong()/_IMG_DEPTH_));

	}

};

#endif
