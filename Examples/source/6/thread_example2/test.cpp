/**
 * 6.3.2 : Test Implementation
 */

/**
 * Includes
 */
#include "test.h"

/**
 * Test Implementation
 */

/** void test::Process_A( void ) : Thread A **/
void test::Process_A(void) {

	cout << sc_time_stamp() << " Process_A : State 1 " << endl;

	// Wait before transitioning
	wait(t1);

	cout << sc_time_stamp() << " Process_A : State 2 " << endl;

	// Wait before transitioning
	wait(t2);

	cout << sc_time_stamp() << " Process_A : State 3 " << endl;

	// Wait before exiting
	wait(t3);

}

/** void test::Process_B( void ) : Thread B **/
void test::Process_B(void) {

	cout << sc_time_stamp() << " Process_B : State 1 " << endl;

	// Wait before transitioning
	wait(t1);

	cout << sc_time_stamp() << " Process_B : State 2 " << endl;

	// Wait before transitioning
	wait(t2);

	cout << sc_time_stamp() << " Process_B : State 3 " << endl;

	// Wait before exiting
	wait(t3);

}

/** void test::Process_C( void ) : Thread C **/
void test::Process_C(void) {

	cout << sc_time_stamp() << " Process_C : State 1 " << endl;

	// Wait before transitioning
	wait(t1);
	
	cout << sc_time_stamp() << " Process_C : State 2 " << endl;

	// Wait before transitioning
	wait(t2);

	cout << sc_time_stamp() << " Process_C : State 3 " << endl;

	// Wait before exiting
	wait(t3);

}

/** void test::Process_D( void ) : Thread D **/
void test::Process_D(void) {

	cout << sc_time_stamp() << " Process_D : State 1 " << endl;

	// Wait before transitioning
	wait(t1);

	cout << sc_time_stamp() << " Process_D : State 2 " << endl;

	// Wait before transitioning
	// Note that SC_ZERO_TIME represents a delta cycle of 0s, mainly to indicate pseudo-priority or pseudo-order
	wait(SC_ZERO_TIME);

	cout << sc_time_stamp() << " Process_D : State 3 " << endl;

	// Wait before exiting
	wait(t3);

}