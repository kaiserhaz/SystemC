/**
 * 6.5.2 : Simple Spawn Implementation
 */

/**
 * Includes
 */
#include "simple_spawn.h"

/**
 * Simple Spawn Implementation
 */

/** Functor structure to get return values **/
struct Functor {

	typedef int result_type;

	result_type operator() ();
};

/** Functor::result_type::operator() ( ) : Implementation of the bracket operator for Functor structure **/
Functor::result_type Functor::operator() () {

	// return a spawned_thread instance
	return spawned_thread();

}

/** int spawned_thread( ) : Non-member thread; to be spawned **/
int spawned_thread() {

	cout << sc_time_stamp() << " : INFO: spawned_thread() Starting " << endl;

	wait(70, SC_NS);

	cout << sc_time_stamp() << " : INFO: spawned_thread() Exiting " << endl;

	return 0;

}

/** int spawned_method( ) : Non-member method; to be spawned **/
int spawned_method() {

	cout << sc_time_stamp() << " : INFO: spawned_method() Starting " << endl;

	return 0;

}

/** int h( ) : Non-member method; to be spawned **/
int h(int a, int& b, const int& c) {

	cout << sc_time_stamp() << " : INFO: h() Starting " << endl;
	
	b = a + 1;
	
	return 0;

}

/** void simple_spawn::g( ) : Member method; to be spawned **/
void simple_spawn::g() {

	cout << sc_time_stamp() << " : INFO: g() Starting " << endl;

}

/** void simple_spawn::main_thread( ) : Module's main thread **/
void simple_spawn::main_thread() {

	// Spawn a function without arguments and discard any return value
	cout << sc_time_stamp() << " : Create 1 : spawned_thread" << endl;

	sc_spawn(&spawned_thread); // spawned_thread thread created here

	// Spawn a similar process and create a process handle
	cout << sc_time_stamp() << " : Create 2 : spawned_thread" << endl;

	sc_process_handle handle = sc_spawn(&spawned_thread); // Get process handle when spawning

	Functor fr;
	int ret;

	// Spawn a function object and catch the return value
	sc_spawn(&ret, fr);

	// Spawn a method named "g1", sensitive to clock, not initialized
	cout << sc_time_stamp() << " : Create 1 : spawned_method" << endl;

	sc_spawn_options opt; // Options to set to spawned process
		opt.spawn_method();
		opt.set_sensitivity(&clk);
		opt.dont_initialize();

	sc_spawn(spawned_method, "g1", &opt); // Options passed as reference

	// Spawn a similar process named "f2" and catch the return value
	cout << sc_time_stamp() << " : Create 4 : spawned_thread" << endl;

	sc_spawn_options opt2;
		opt2.set_sensitivity(&clk);
	
	sc_spawn(&ret, fr, "f2", &opt2);

	// Spawn a member function using Boost bind
	cout << sc_time_stamp() << " : Create 2 : g()" << endl;

	sc_spawn( sc_bind(&simple_spawn::g, this) );

	// Spawn a function using Boost bind, pass arguments
	// and catch the return value
	cout << sc_time_stamp() << " : Create 1 : h()" << endl;

	int A = 0, B, C;

	sc_spawn(&ret, sc_bind(&h, A, sc_ref(B), sc_cref(C)));

	wait(500, SC_NS);

}