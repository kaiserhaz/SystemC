/**
 * @file ad823_unit_test.cpp
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
#include "ad823.h"

// Defs
#define _A_GEN_ 1.65
#define _F_GEN_ 100.0
#define _R_L_   2.0E3
#define _C_L_   2.0E-11

int sc_main(int argc, char *argv[]) {

	sc_set_time_resolution(1.0, SC_NS);

	// DUT
	ad823                               u1("u1");

	// Bench-level components
	
	// Generator
	sca_eln::sca_vsource                v_gen("v_gen", 0, 0, _A_GEN_, _F_GEN_, 0, sc_core::SC_ZERO_TIME, _A_GEN_);
	
	// Load
	sca_eln::sca_r                      r_l("r_l", _R_L_);
	sca_eln::sca_c                      c_l("c_l", _C_L_);
	
	sca_eln::sca_node                   sig_gen_p,
	                                    sig_gen_n,
	                                    sig_out ;
	sca_eln::sca_node_ref               gnd("gnd");
	
	// Port connections
	v_gen.p(sig_gen_p);
	v_gen.n(sig_gen_n);
	
	u1.in_p(sig_gen_p);
	u1.in_n(sig_gen_n);
	u1.out(sig_out);
	u1.cmn(gnd);
	
	r_l.p(sig_out);
	r_l.n(gnd);
	c_l.p(sig_out);
	c_l.n(gnd);
	
	// Set timestep
	v_gen.set_timestep(5.0, SC_NS);
	
	// Output tracefile
	sca_util::sca_trace_file *actf = sca_util::sca_create_tabular_trace_file("ad823_tr.dat");
	sca_util::sca_write_comment(actf, "Frontend unit test simulation");

	sca_util::sca_trace(actf, sig_gen_p , "gen_p");
	sca_util::sca_trace(actf, sig_out , "out");

	// Simulation start
	sca_ac_start(100, 1E8, 55,  sca_ac_analysis::SCA_LOG);
	
	printf("> ad823_unit_test : Simulation done\r\n");

	system("sleep 1");

	return 0;

}
