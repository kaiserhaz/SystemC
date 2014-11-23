/**
 * 9.4.1 : Clock Gen Structure
 */

/**
 * Define guard
 */
#ifndef CLOCK_GEN_H
#define CLOCK_GEN_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Clock Gen Definition
 */
SC_MODULE( clock_gen ) {

	sc_port< sc_signal_out_if<bool> > clk1_p;
	sc_export< sc_signal_out_if<bool> > clk2_p;

	sc_clock clk1;
	sc_clock clk2;

	SC_CTOR( clock_gen ) : clk1("clk1",4,SC_NS), clk2("clk2",6,SC_NS)
	{
		
		SC_METHOD(clk1_method);
			sensitive << clk1;

		clk2_p.bind(clk2);

	}

	void clk1_method() {

		clk1_p->write(clk1);
	
	}

};

#endif
