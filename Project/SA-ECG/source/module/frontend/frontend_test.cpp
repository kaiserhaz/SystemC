/**
 * @file frontend_test.cpp
 *
 * @brief Simulation unit test file for frontend model.
 * 
 * -- Versioning Info --
 *
 * v1.0 : 19/02/2025 : Initial working config write-up.
 * v2.0 : 25/02/2025 : Modified vpulsesource; working as intended now.
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
#include "../surface-ecg/gen_ecg.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream> 

// Defs
#define _A_SINE_  311.0
#define _F_SINE_  50.0
#define _ECG_DAT_FILE_ "../surface-ecg/ecgSig.dat"

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

// ECG generator
SCA_TDF_MODULE( ecggenerator ){
	
	sca_tdf::sca_out<double> out;
	
	SCA_CTOR( ecggenerator ) :
		out("out"),
		file(),
		ecg_data()
	{}
	
	private:
	
	std::ifstream file;
	std::queue<double> ecg_data;
	
	void set_attributes()
	{
		int status = gen_ecg();
		
		if(status!=0)
		{
			SC_REPORT_ERROR(this->name(),"Error occurred in ECG elaboration!");
		}
		
		file.open(_ECG_DAT_FILE_);
		
		if (!file.is_open()) {
			SC_REPORT_ERROR(this->name(),"Unable to open file!");
		}
		
		std::string line;
		
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string value;
			
			while (std::getline(ss, value)) {
				try {
					ecg_data.push(std::stod(value));
				} catch (const std::invalid_argument& e) {
					SC_REPORT_ERROR(this->name(),"Invalid number format");
				}
			}
		}
		
		file.close();
		
		SC_REPORT_INFO(this->name(),"ECG signal loaded. There are ");
		printf("%lu samples available.\r\n", ecg_data.size());
	}
	
	void processing()
	{
		if(ecg_data.empty())
			sc_stop();
		
		out.write( ecg_data.front() );
		ecg_data.pop();
	}
	
};

int sc_main(int argc, char *argv[]) {
	
	// DUT
	frontend                            u1("u1");

	// Bench-level components
	
	// Human-sector coupling model
	vsinesource                         v_sector("v_sector");
	ecggenerator                        v_ecg("v_ecg");
	sca_eln::sca_tdf_vsource            v_sector_conv("v_sector_conv");
	sca_eln::sca_tdf_vsource            v_ecg_conv("v_ecg_conv", 1e-3);
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
	
	sca_tdf::sca_signal<double>         sig_sine,
	                                    sig_ecg;
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
	
	v_ecg.out(sig_ecg);
	v_ecg_conv.inp(sig_ecg);
	v_ecg_conv.p(sig_in_el_p);
	v_ecg_conv.n(sig_bd);
	
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
	
	v_ecg_conv.set_timestep(100.0, SC_US);
	
	// Output tracefile
	sca_util::sca_trace_file *trtf = sca_util::sca_create_tabular_trace_file("frontend_tr.dat");
	sca_util::sca_write_comment(trtf, "Frontend unit test simulation");

	sca_util::sca_trace(trtf, sig_sector_p, "sector_p");
	sca_util::sca_trace(trtf, sig_in_el_p, "in_el_p");
	sca_util::sca_trace(trtf, sig_out , "out");

	// Simulation start
	sca_core::sca_set_default_solver_parameter("sca_linear_solver","algorithm","euler");
	sc_start();
	
	printf("> frontend_test : Simulation done\r\n");

	system("sleep 1");

	return 0;

}
