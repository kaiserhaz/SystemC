/**
 * 7.3.2 : Signal Implementation
 */

/**
 * Includes
 */
#include <systemc.h>
#include "signal.h"

/**
 * Signal Implementation
 */

/** Threads **/

/** void trans_thread_ ( void ) : Main thread for the transactor **/
void signal::P1_thread(void) {

	// Initializing during 1st delta cycle
	cout << " P1 : P1_thread is initializing " << endl;
	
	count_sig.write(10);
	
	traffic_sig.write(BLACK);
	message_sig.write("Hello");
	
	count = 11;

	traffic_temp = RED;
	message_temp = "Whoa";

	// wait 10 ms cycle
	wait(10, SC_MS);

	cout << " P1 : P1_thread is done initializing " << endl;
	
	count = 20;
	count_sig.write(count);

	cout << " P1 : count is " << count << " count_sig is " << count_sig.read() << endl;
	cout << " P1 : P1_thread is waiting " << endl;

	// wait 5 ms
	wait(5, SC_MS);

	cout << " P1 : count is " << count << " count_sig is " << count_sig.read() << endl;

	traffic_sig.write(traffic_temp = WHITE);

	cout << " P1 : traffic_temp is '" << traffic_temp << "' traffic_sig '" << traffic_sig.read() << "'" << endl;
	
	message_sig.write(message_temp = "Rev your engines");
	
	cout << " P1 : message_temp is '" << message_temp << "' message_sig '" << message_sig.read() << "'" << endl;

	// wait 10 ms
	wait(10, SC_MS);

	cout << " P1 : P1_thread done " << endl;

}

/** void trans_thread_ ( void ) : Main thread for the transactor **/
void signal::P2_method(void) {

	cout << " P2 : detected an EVENT! @" << sc_time_stamp() << endl;

	cout << " P2 : count = " << count << " count_sig = " << count_sig.read() << endl;

	cout << " P2 : traffic_temp = " << traffic_temp << " traffic_sig = " << traffic_sig.read() << endl;

	cout << " P2 : message_temp = '" << message_temp << "' message_sig = '" << message_sig.read() << "'" << endl;

}
