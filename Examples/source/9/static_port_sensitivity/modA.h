/**
 * 9.2.2 : modA Structure
 */

/**
 * Define guard
 */
#ifndef MODA_H
#define MODA_H

/**
 * Includes
 */
#include <systemc.h>
#include "my_port_sc_signal_in_if_bool.h"

/**
 * modA Module Definition
 */
SC_MODULE( modA ) {

	/** modA Ports **/

	my_port_sc_signal_in_if_bool my_port;
	sc_out<int> cpt_o;

	/** modA Fields **/

	int cpt;

	/** modA Constructor **/

	SC_CTOR(modA) : cpt(0)
	{
		// Method declaration
		SC_METHOD(modA_method);
			dont_initialize();

		sensitive << my_port.ef_posedge_event();
	}

	/** modA Methods **/

	void modA_method(void) {

		cout << sc_time_stamp() << " Event ! " << cpt << endl;

		cpt_o->write(cpt);

		cpt++;

	}


};

#endif
