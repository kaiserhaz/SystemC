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
#include "frontend.h"
#include <cmath>

// Defs
#define _T_SIM_ 20.0
#define _A_PULSE_ 5E-4

// Pulsed source definition in TDF (for ease of process using math tools)
SCA_TDF_MODULE( vpulsesource ){
	
	sca_tdf::sca_out out, out_inv;
	
	SCA_CTOR( vpulsesource ) :
		out("out"), out_inv("out_inv")
	{
		
	}
	
	private:
	
	void set_attributes()
	{
		out.set_timestep(2.0, SC_US);
		out_inv.set_timestep(2.0, SC_US);
	}
	
	void processing()
	{
		double t = out.get_time().to_seconds();
		out.write( _A_PULSE_ * std::power( std::cos(2.0*M_PI*2*t), 6.0 ) ); // Pulse shape from elevating powers of cosine
		out_inv.write( -_A_PULSE_ * std::power( std::cos(2.0*M_PI*2*t), 6.0 ) );
	}
	
}

int sc_main(int argc, char *argv[]) {

	sc_set_time_resolution(1.0, SC_US);

	// DUT
	frontend                            u1("u1");

	// Bench-level components
	
	// Human-sector coupling model
	sca_eln::sca_vsource                v_sector("v_sector", 0, 0, 311, 50, 0, SC_ZERO_TIME, 311);
	vpulsesource                        v_pulse("v_pulse");
	sca_eln::sca_r                      r_bd("r_bd", 1E2);
	sca_eln::sca_c                      c_pb("c_l", 2E-12), c_bg("c_l", 150E-12);
	
	// Electrode impedance model
	sca_eln::sca_r                      r_in_p("r_in_p", 2E3);
	sca_eln::sca_c                      c_in_p("c_in_p", 1E-8);
	sca_eln::sca_r                      r_in_n("r_in_p", 2E3);
	sca_eln::sca_c                      c_in_n("c_in_p", 1E-8);
	
	// Output model
	sca_eln::sca_r                      r_l("r_l", 2E3);
	sca_eln::sca_c                      c_l("c_l", 1.5E-8);
	
	
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
	v_sector.p(sig_sector_p);
	v_sector.n(gnd);
	
	c_pb.p(sig_sector_p);
	c_pb.n(sig_in_el_p);
	
	v_pulse.out(sig_in_el_p);
	v_pulse.out_inv(sig_bd);
	
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
	
	// Timestep fixing
	v_sector.set_timestep(2.0, SC_US);

	// Output tracefile
	sca_util::sca_trace_file *trtf = sca_util::sca_create_tabular_trace_file("frontend_tr.dat");
	sca_util::sca_write_comment(actf, "Frontend unit test simulation");

	sca_util::sca_trace(trtf, sig_in_el_p, "in_el_p");
	sca_util::sca_trace(trtf, sig_out , "out");

	// Simulation start
	sc_start(_T_SIM_, SC_SECONDS);
	
	printf("> frontend_unit_test : Simulation done");

	system("sleep 1");

	return 0;

}
