#ifndef USER_H // user include guard
#define USER_H

#include <systemc.h>

/**
 * user module definition
 */

SC_MODULE( user ) {

	/**
	 * Input output port declarations
	 */

	sc_out<double> period; // Module's output, specifying a period in ns
	sc_out<bool> reset;    // Module's reset signal output
	sc_out<bool> up_down;  // Module's count up-count down signal output
	sc_out<bool> load;     // Module's load signal output
	sc_out<int> data_in;   // Module's output data

	/**
	 * SystemC macro constructor for this module
	 */

	SC_CTOR( user ) : period("period"), reset("reset"), up_down("up_down"), load("load"), data_in("data_in")
	{
		SC_THREAD( user_thread ); // Register this module's process with the SystemC kernel as an SC_THREAD
	}

	/**
	 * Module's thread
	 */

	void user_thread(void) {

		while(true) {

			reset->write(false);   // Deactivate reset
			period->write(10.0);   // Change period
			up_down->write(false); // Set to count up
			wait(100, SC_NS);

			period->write(5.0);   // Change period
			up_down->write(true); // Set to count down
			wait(50, SC_NS);

			load->write(true); // Set load signal to high
			data_in->write(4); // Write data to load
			wait(15, SC_NS);

			load->write(false); // Set load signal to low
			wait(50, SC_NS);

			reset->write(true); // Activate reset
			wait(10, SC_NS);

		}

	}

};

#endif