#ifndef MOD_10_COUNTER_H // mod_10_counter include guard
#define MOD_10_COUNTER_H

#include <systemc.h>

/**
 * mod_10_counter module definition
 */

SC_MODULE( mod_10_counter ) {

	/**
	 * Input output port declarations
	 */

	sc_in<double> period; // Module's clock period
	sc_in<bool> reset;    // Module's reset signal
	sc_in<bool> up_down;  // Module's count up-count down toggle signal
	sc_in<bool> load;     // Module's load enable signal
	sc_in<int> data_in;   // Module's input data
	sc_out<int> q;        // Module's output
	
	/**
	 * SystemC macro constructor for this module
	 */

	SC_CTOR( mod_10_counter ) : period("period"), reset("reset"), up_down("up_down"), load("load"), data_in("data_in"), q("q")
	{
		SC_THREAD( mod_10_counter_thread ); // Register this module's process with the SystemC kernel as an SC_THREAD
	}
	
	void mod_10_counter_thread(void); // Module's thread prototype

};

#endif