#ifndef DAC_H
#define DAC_H

#include <systemc-ams.h>

#define _V_MAX_ 5

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

		dac_r.set_timestep(20, SC_NS); // 50 Msps is minimum rate
		dac_g.set_timestep(20, SC_NS);
		dac_b.set_timestep(20, SC_NS);

	}

	void processing() {

		dac_r.write(vga_r.read().to_int());
		dac_g.write(vga_g.read().to_int());
		dac_b.write(vga_b.read().to_int());

	}

};

#endif
