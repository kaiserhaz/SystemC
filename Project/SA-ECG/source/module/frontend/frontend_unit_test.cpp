/**
 * @file frontend_unit_test.cpp
 *
 * @brief Simulation unit test file for frontend model.
 * 
 * -- Versioning Info --
 *
 * v1.0 : 19/02/2025 : Initial working config write-up.
 *
 * @copyright
 * Copyright 2025 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */
 
 // Libs
#include <systemc.h>
#include "frontend.h"
#include <cmath>

// Defs
#define _T_SIM_   12.0
#define _A_SINE_  311.0
#define _F_SINE_  50.0
#define _A_PULSE_ 5.0E-4

// Sine source definition in TDF (for ease of process using math tools)
SCA_TDF_MODULE( vsinesource ){
	
	sca_tdf::sca_out<double> out;
	
	SCA_CTOR( vsinesource ) :
		out("out")
	{}
	
	private:
	
	void processing()
	{
		double t = out.get_time().to_seconds();
		out.write( _A_SINE_ * std::sin(2.0*M_PI*_F_SINE_*t) );
	}
	
};

// Pulsed source definition in TDF (for ease of process using math tools)
SC_MODULE( vpulsesource ){
	
	sc_in_clk clk_in;
	sc_out<double> pulse_out;
	
	SC_CTOR( vpulsesource ) :
		clk_in("clk_in")      ,
		pulse_out("pulse_out"),
		pulse_cnt(0)
	{
		SC_METHOD(pulse);
			sensitive << clk_in.pos();
	}
	
	private:
	
	unsigned int pulse_cnt=0;
	
	void pulse()
	{	
		if (pulse_cnt==0)               
		{
			pulse_out->write(1.0);
		}
		
		if (pulse_cnt==120)             // 120ms
		{
			pulse_out->write(0.0);
		}
		
		pulse_cnt += 1;
		pulse_cnt %= 990;
		
		next_trigger(clk_in.posedge_event());
	}
	
};

int sc_main(int argc, char *argv[]) {
	
	// DUT
	frontend                            u1("u1");

	// Bench-level components
	
	// Clock
	sc_clock                            pulse_clk("pulse_clk", 1.0, SC_MS);
	
	// Human-sector coupling model
	vsinesource                         v_sector("v_sector");
	vpulsesource                        v_pulse("v_pulse");
	sca_eln::sca_tdf_vsource            v_sector_conv("v_sector_conv");
	sca_eln::sca_de::sca_vsource        v_pulse_conv("v_pulse_conv", _A_PULSE_);
	sca_eln::sca_r                      r_bd("r_bd", 1E2);
	sca_eln::sca_c                      c_pb("c_pb", 2E-12, sca_util::SCA_UNDEFINED),
	                                    c_bg("c_bg", 150E-12, sca_util::SCA_UNDEFINED);
	
	// Electrode impedance model
	sca_eln::sca_r                      r_in_p("r_in_p", 2E3);
	sca_eln::sca_c                      c_in_p("c_in_p", 10E-9, sca_util::SCA_UNDEFINED);
	sca_eln::sca_r                      r_in_n("r_in_n", 2E3);
	sca_eln::sca_c                      c_in_n("c_in_n", 10E-9, sca_util::SCA_UNDEFINED);
	
	// Output model
	sca_eln::sca_r                      r_l("r_l", 2E3);
	sca_eln::sca_c                      c_l("c_l", 15E-9, sca_util::SCA_UNDEFINED);
	
	sca_tdf::sca_signal<double>         sig_sine;
	sc_signal<double>                   sig_pulse;
	sca_eln::sca_node                   sig_sector_p,
	                                    sig_in_p,
	                                    sig_in_n,
										sig_in_el_p,
										sig_in_el_n,
										sig_bd,
										sig_u_out,
										sig_out ;
	sca_eln::sca_node_ref               gnd("gnd");
	
	// Port connections
	
	v_sector.out(sig_sine);
	v_sector_conv.inp(sig_sine);
	v_sector_conv.p(sig_sector_p);
	v_sector_conv.n(gnd);
	
	c_pb.p(sig_sector_p);
	c_pb.n(sig_in_el_p);
	
	v_pulse.clk_in(pulse_clk);
	v_pulse.pulse_out(sig_pulse);
	v_pulse_conv.inp(sig_pulse);
	v_pulse_conv.p(sig_in_el_p);
	v_pulse_conv.n(sig_bd);
	
	r_bd.p(sig_bd);
	r_bd.n(sig_in_el_n);
	
	c_bg.p(sig_in_el_n);
	c_bg.n(gnd);
	
	r_in_p.p(sig_in_el_p);
	r_in_p.n(sig_in_p);
	c_in_p.p(sig_in_el_p);
	c_in_p.n(sig_in_p);
	
	r_in_n.p(sig_in_el_n);
	r_in_n.n(sig_in_n);
	c_in_n.p(sig_in_el_n);
	c_in_n.n(sig_in_n);
	
	u1.in_p(sig_in_p);
	u1.in_n(sig_in_n);
	u1.out(sig_u_out);
	u1.cmn(gnd);
	
	r_l.p(sig_u_out);
	r_l.n(sig_out);
	c_l.p(sig_out);
	c_l.n(gnd);
	
	v_pulse_conv.set_timestep(1000.0, SC_US);
	
	// Output tracefile
	sca_util::sca_trace_file *trtf = sca_util::sca_create_tabular_trace_file("frontend_tr.dat");
	sca_util::sca_write_comment(trtf, "Frontend unit test simulation");

	sca_util::sca_trace(trtf, sig_sector_p, "sector_p");
	sca_util::sca_trace(trtf, sig_in_el_p, "in_el_p");
	sca_util::sca_trace(trtf, sig_out , "out");

	// Simulation start
	sc_start(_T_SIM_, SC_SEC);
	
	printf("> frontend_unit_test : Simulation done\r\n");

	system("sleep 1");

	return 0;

}
