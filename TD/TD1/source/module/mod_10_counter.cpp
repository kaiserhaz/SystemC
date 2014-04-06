#include <systemc.h>
#include "mod_10_counter.h"

/**
 * mod_10_counter member functions definition
 */

/**
 * mod_10_counter_thread : the module's main thread
 */

void mod_10_counter::mod_10_counter_thread(void) {

	int c; // Temporary variable, with initialisation at the following line
	c = 0;

	//cout << " COUNTER : ENTERING LOOP " << endl;
	
	while(true) {
		
		//cout << " COUNTER : AWAITING RESET OR TIMEOUT " << endl;

		/* 
		 * Wait for the specified period of time, or an event on the reset signal
		 */
		wait((double)mod_10_counter::period->read(), SC_NS, mod_10_counter::reset->default_event()/*mod_10_counter::reset->posedge_event() | mod_10_counter::reset->negedge_event()*/);
		
		/*
		 * If the reset signal is high, reset the counter (c <= 0), else continue to the main process
		 */
		if(mod_10_counter::reset->read() == true) {

			c = 0;

			//cout << " COUNTER : RESET " << endl;

		}
		else {

			/*
			 * If the load signal is high, then we load the specified value into the temporary variable, else continue to the count process
			 */
			if(mod_10_counter::load->read() == true) {

				c = mod_10_counter::data_in->read();

				//cout << " COUNTER : LOAD " << endl;

			}
			else {

				/*
				 * If the count up-count down signal is low, we count up, else we count down, in both cases doing a modulo 10
				 */
				if(mod_10_counter::up_down->read() == false) {

					c = (int)(c+1)%10;

					//cout << " COUNTER : COUNT UP " << endl;

				}
				else {

					c = (int)(c-1);

					/*
					 * Modulo operator is not very reliable for counting down, therefore we use this technique to simulate a modulo
					 */
					if(c < 0)
						c = 9;

					//cout << " COUNTER : COUNT DOWN " << endl;

				}

			}

		}
		
		mod_10_counter::q->write(c); // Finally, we write to the output port
		
		//cout << " COUNTER : OUTPUT WRITTEN " << endl;

	}
	
}