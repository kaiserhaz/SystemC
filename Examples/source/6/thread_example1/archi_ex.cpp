/**
 * 6.2.2 : Architecture Implementation
 */

/**
 * Includes
 */
#include "archi_ex.h"

/**
 * Architecture Implementation
 */

/** void user_thread( void ) : User's main thread **/
void archi_ex::user_thread(void) {

	// Loop
	for(int i = 0; i <= 5; i++) {

		cout << sc_time_stamp() << " user : notified count event (" << i <<")" << endl;

		// Send COUNT message to counter process
		from_usermess = COUNT;

		// Notify a count event with incremental wait
		count.notify(1+i, SC_NS);

		cout << sc_time_stamp() << " user : waiting ok or restart events" << endl;

		// Wait for ok or restart event
		wait(ok | restart);

		if(from_countermess == OK)
			cout << sc_time_stamp() << " user : ok !" << endl; // If ok
		else
			cout << sc_time_stamp() << " user : restart !" << endl; // If restart

	}

	cout << "----------------------------------------------" << endl;
	
	wait(20, SC_NS);

	cout << sc_time_stamp() << " user : reset" << endl;

	// Send RESET message
	from_usermess = RESET;

	// Notify reset
	reset.notify();

	cout << sc_time_stamp() << " user : waiting restart event" << endl;

	// Wait on restart event
	wait(restart);
}

/** void counter_9_thread( void ) : Counter's main thread **/
void archi_ex::counter_9_thread(void) {

	// Loop
	while(true) {

		cout << sc_time_stamp() << " counter : waiting count or reset event " << endl;

		// Wait on count or reset event
		wait(count | reset);

		cout << sc_time_stamp() << " counter : receiving count or reset event " << endl;

		if(from_usermess == RESET)
			n = 0; // If reset
		else
			n += 1 % 10;

		// If n == 0 : a reset has occurred
		if(n == 0) {

			from_countermess = RESTART; // Send RESTART message to user
			restart.notify(); // Notify restart
		}
		// Else
		else {

			from_countermess = OK; // Send OK message to user
			ok.notify(); // Notify ok
		
		}

	}

}