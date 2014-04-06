/**
 * 4.3.2 : Simple Process Implementation
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

	std::cout << "my_thread_process executed within " << name() << std::endl;

}