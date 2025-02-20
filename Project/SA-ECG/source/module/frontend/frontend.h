/**
 * @file frontend.h
 *
 * @brief Two-electrode frontend circuit from (Dobrev, Neycheva and Mudrov 2005).
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
#ifndef FRONTEND_H
#define FRONTEND_H

// Libs
#include <systemc-ams.h>
#include "ad823.h"

// Defs
#define _R_FB_ 2.5E5
#define _R_GM_ 2.5E5
#define _C_FB_ 4.6E-12

/**
 * Frontend circuit module
 */
SC_MODULE( frontend ) {

	// Attibutes: ports
	sca_eln::sca_terminal in_p;
	sca_eln::sca_terminal in_n;
	sca_eln::sca_terminal out;
	sca_eln::sca_terminal cmn;
	
	// Constructor
	SC_CTOR( frontend ) :
		r_fb("r_fb", _R_FB_),
		r_gm("r_gm", _R_GM_),
		c_fb("c_fb", _C_FB_, sca_util::SCA_UNDEFINED),
		u_fb("u_fb"),
		u_vf("u_vf"),
		trn ("trn")
	{
		// Input-output port bindings
		r_gm.n(in_p);
		u_vf.in_p(in_p);
		
		r_fb.p(in_n);
		c_fb.p(in_n);
		u_fb.in_n(in_n);
		
		u_vf.in_n(out);
		u_vf.out(out);
		
		u_fb.in_p(cmn);
		u_fb.cmn(cmn);
		u_vf.cmn(cmn);
		
		// Internal circuitry bindings
		r_fb.n(trn);
		c_fb.n(trn);
		u_fb.out(trn);
		r_gm.p(trn);
	}

	private:

	// Attributes: components
	sca_eln::sca_r r_fb;
	sca_eln::sca_r r_gm;
	sca_eln::sca_c c_fb;
	ad823          u_fb, u_vf;
	
	// Attributes: nodes
	sca_eln::sca_node trn;
	
};

#endif
