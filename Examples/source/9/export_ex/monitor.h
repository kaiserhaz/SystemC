/**
 * 9.4.2 : Monitor Structure
 */

/**
 * Define guard
 */
#ifndef MONITOR_H
#define MONITOR_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Monitor Definition
 */
SC_MODULE( monitor ) {

	sc_in<bool> clk1_p;
	sc_in<bool> clk2_p;

	SC_CTOR( monitor ) {

		SC_METHOD(clk1_method);
			sensitive << clk1_p;

		SC_METHOD(clk2_method);
			sensitive << clk2_p;

	}

	void clk1_method() {

		cout << name() << " clk1 = " << clk1_p->read() << " at " << sc_time_stamp() << endl;

	}

	void clk2_method() {

		cout << name() << " clk2 = " << clk2_p->read() << " at " << sc_time_stamp() << endl;

	}

};

#endif
