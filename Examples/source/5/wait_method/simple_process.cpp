/**
 * 5.5.2 : Simple Process Implementation
 */

/**
 * Includes
 */
#include "simple_process.h"

/**
 * Simple Process Implementation
 */

/** void my_thread_process( void ) : Simple Process' main thread **/
void simple_process::my_thread_process(void) {

	std::cout << " Now at " << sc_time_stamp() << std::endl;

	// Wait for 10 ns
	wait(10, SC_NS);

	std::cout << " Now at " << sc_time_stamp() << std::endl;

	sc_time t (5, SC_NS);

	// Computes delay
	t = t * 3;

	std::cout << " Delaying " << t << std::endl;

	// Waiting
	wait(t);

	std::cout << " Now at " << sc_time_stamp() << std::endl;

}
