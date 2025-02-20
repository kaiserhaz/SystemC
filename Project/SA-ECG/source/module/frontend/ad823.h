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
#define _V_B_ 2.5E-3
#define _C_IN_ 1.8E-12
#define _R_IN_S_ 1.0E13
#define _R_IN_D_ 1.0E10
#define _I_B_ 2.5E-11
#define _I_OFF_ 2.0E-11
#define _G_T_ 1.0
#define _R_T_ 3.0E4
#define _C_P_ 1.768E-8
#define _A_V_ 1.0
#define _R_OUT_ 1.0E-2

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
		v_b   ("v_b", 0, 0, _V_B_),
		c_in_d("c_in_d", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_d("r_in_d", _R_IN_D_),
		c_in_p("c_in_p", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_p("r_in_p", _R_IN_S_),
		i_b_p ("i_b_p", _I_B_-_I_OFF_),
		i_off ("i_off", _I_OFF_),
		c_in_n("c_in_n", _C_IN_, sca_util::SCA_UNDEFINED),
		r_in_n("r_in_n", _R_IN_S_),
		i_b_n ("i_b_n", _I_B_),
		g_t   ("g_t", _G_T_),
		r_t   ("r_t", _R_T_),
		c_p   ("c_p", _C_P_),
		a_v   ("a_v", _A_V_),
		r_out ("r_out", _R_OUT_),
		pside ("pside"),
		cside ("cside"),
		oside ("oside"),
		cmn   ("cmn")
	{
		// Input-output port bindings
		v_b.p(in_p);
		v_b.n(pside);
		
		c_in_d.n(in_n);
		r_in_d.n(in_n);
		g_t.ncn(in_n);
		c_in_n.p(in_n);
		r_in_n.p(in_n);
		i_b_n.p(in_n);
		
		r_out.n(out);
		
		c_in_p.n(cmn);
		r_in_p.n(cmn);
		i_b_p.n(cmn);
		i_off.n(cmn);
		c_in_n.n(cmn);
		r_in_n.n(cmn);
		i_b_n.n(cmn);
		g_t.nn(cmn);
		r_t.n(cmn);
		c_p.n(cmn);
		a_v.ncn(cmn);
		a_v.nn(cmn);
		
		// Internal circuitry bindings
		c_in_d.p(pside);
		r_in_d.p(pside);
		g_t.ncp(pside);
		c_in_p.p(pside);
		r_in_p.p(pside);
		i_b_p.p(pside);
		i_off.p(pside);
		
		g_t.np(cside);
		r_t.p(cside);
		c_p.p(cside);
		a_v.ncp(cside);
		
		a_v.np(oside);
		r_out.p(oside);
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
	sca_eln::sca_vccs g_t;
	sca_eln::sca_r r_t;
	sca_eln::sca_c c_p;
	sca_eln::sca_vcvs a_v;
	sca_eln::sca_r r_out;

	// Attributes: nodes
	sca_eln::sca_node pside, cside, oside;
	
};

#endif
