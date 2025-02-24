/**
 * @file ad823.h
 *
 * @brief Analog Devices AD823 FET Input Amplifier model.
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

// Def guard
#ifndef AD823_H
#define AD823_H

// Libs
#include <systemc-ams.h>

// Defs
#define _V_B_    2.5E-9
#define _C_IN_   1.8E-12
#define _R_IN_S_ 1.0E13
#define _R_IN_D_ 1.0E10
#define _I_B_    2.5E-11
#define _I_OFF_  2.0E-11
#define _G_1_    1.0
#define _R_1_    3.0E4
#define _C_1_    5.894E-8
#define _G_2_    1.0
#define _R_2_    1.0E4
#define _C_2_    0.357E-12
#define _A_V_    1.0
#define _R_OUT_  1.0E-2

/**
 * AD823 circuit module
 */
SC_MODULE( ad823 ) {

	// Attibutes: ports
	sca_eln::sca_terminal in_p;
	sca_eln::sca_terminal in_n;
	sca_eln::sca_terminal out;
	sca_eln::sca_terminal cmn;
	
	// Constructor
	SC_CTOR( ad823 ) :
		v_b   ("v_b", 0, _V_B_),
		c_in_d("c_in_d", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_d("r_in_d", _R_IN_D_),
		c_in_p("c_in_p", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_p("r_in_p", _R_IN_S_),
		i_b_p ("i_b_p", _I_B_-_I_OFF_),
		i_off ("i_off", _I_OFF_),
		c_in_n("c_in_n", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_n("r_in_n", _R_IN_S_),
		i_b_n ("i_b_n", _I_B_),
		g_1   ("g_1", _G_1_),
		r_1   ("r_1", _R_1_),
		c_1   ("c_1", _C_1_),
		g_21  ("g_21", _G_2_),
		r_21  ("r_21", _R_2_),
		c_21  ("c_21", _C_2_),
		g_22  ("g_22", _G_2_),
		r_22  ("r_22", _R_2_),
		c_22  ("c_22", _C_2_),
		g_23  ("g_23", _G_2_),
		r_23  ("r_23", _R_2_),
		c_23  ("c_23", _C_2_),
		g_24  ("g_24", _G_2_),
		r_24  ("r_24", _R_2_),
		c_24  ("c_24", _C_2_),
		a_v   ("a_v", _A_V_),
		r_out ("r_out", _R_OUT_),
		pside ("pside"),
		g1side ("g1side"),
		g21side ("g21side"),
		g22side ("g22side"),
		g23side ("g23side"),
		g24side ("g24side"),
		oside ("oside")
	{
		// Bias voltage
		v_b.p(in_p);
		v_b.n(pside);
		
		// Input stage
		c_in_d.p(pside);
		c_in_d.n(in_n);
		r_in_d.p(pside);
		r_in_d.n(in_n);
		g_1.ncp(pside);
		g_1.ncn(in_n);
		
		// Positive-side bias stage
		c_in_p.p(pside);
		c_in_p.n(cmn);
		r_in_p.p(pside);
		r_in_p.n(cmn);
		i_b_p.p(pside);
		i_b_p.n(cmn);
		i_off.p(pside);
		i_off.n(cmn);
		
		// Negative-side bias stage
		c_in_n.p(in_n);
		c_in_n.n(cmn);
		r_in_n.p(in_n);
		r_in_n.n(cmn);
		i_b_n.p(in_n);
		i_b_n.n(cmn);
		
		// First gain-pole stage
		g_1.np(g1side);
		g_1.nn(cmn);
		r_1.p(g1side);
		r_1.n(cmn);
		c_1.p(g1side);
		c_1.n(cmn);
		
		// Second gain-pole stage
		g_21.ncp(g1side);
		g_21.ncn(cmn);
		g_21.np(g21side);
		g_21.nn(cmn);
		r_21.p(g21side);
		r_21.n(cmn);
		c_21.p(g21side);
		c_21.n(cmn);
		g_22.ncp(g21side);
		g_22.ncn(cmn);
		g_22.np(g22side);
		g_22.nn(cmn);
		r_22.p(g22side);
		r_22.n(cmn);
		c_22.p(g22side);
		c_22.n(cmn);
		g_23.ncp(g22side);
		g_23.ncn(cmn);
		g_23.np(g23side);
		g_23.nn(cmn);
		r_23.p(g23side);
		r_23.n(cmn);
		c_23.p(g23side);
		c_23.n(cmn);
		g_24.ncp(g23side);
		g_24.ncn(cmn);
		g_24.np(g24side);
		g_24.nn(cmn);
		r_24.p(g24side);
		r_24.n(cmn);
		c_24.p(g24side);
		c_24.n(cmn);	
		
		// Output stage
		a_v.ncp(g24side);
		a_v.ncn(cmn);
		a_v.np(oside);
		a_v.nn(cmn);
		r_out.p(oside);
		r_out.n(out);
	}

	private:

	// Attributes: components
	sca_eln::sca_vsource v_b;
	sca_eln::sca_c c_in_d;
	sca_eln::sca_r r_in_d;
	sca_eln::sca_c c_in_p;
	sca_eln::sca_r r_in_p;
	sca_eln::sca_isource i_b_p;
	sca_eln::sca_isource i_off;
	sca_eln::sca_c c_in_n;
	sca_eln::sca_r r_in_n;
	sca_eln::sca_isource i_b_n;
	sca_eln::sca_vccs g_1;
	sca_eln::sca_r r_1;
	sca_eln::sca_c c_1;
	sca_eln::sca_vccs g_21;
	sca_eln::sca_r r_21;
	sca_eln::sca_c c_21;
	sca_eln::sca_vccs g_22;
	sca_eln::sca_r r_22;
	sca_eln::sca_c c_22;
	sca_eln::sca_vccs g_23;
	sca_eln::sca_r r_23;
	sca_eln::sca_c c_23;
	sca_eln::sca_vccs g_24;
	sca_eln::sca_r r_24;
	sca_eln::sca_c c_24;
	sca_eln::sca_vcvs a_v;
	sca_eln::sca_r r_out;

	// Attributes: nodes
	sca_eln::sca_node pside  ,
	                  g1side ,
	                  g21side,
	                  g22side,
	                  g23side,
	                  g24side,
					  oside  ;
	
};

#endif
