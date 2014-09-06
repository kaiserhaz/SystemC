/**
 * 7.1.1 : testsem Structure
 */

/**
 * Define guard
 */
#ifndef TESTSEM_H
#define TESTSEM_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * testsem Module Definition
 */
SC_MODULE( testsem ) {

	/** testsem Member Declaration **/
	sc_semaphore sem;

	/** testsem Constructor **/
	SC_CTOR( testsem ) : sem("sem", 0) {

		// Thread declaration
		SC_THREAD( p1 );
		SC_THREAD( p2 );

	}

	/** Simple Process Threads **/
	void p1() {

		// Forever loop
		while (true) {

			wait(10, SC_MS);

			cout << sc_time_stamp() << " : P1 = Post 1" << endl;

			// Do a post : increment counter
			sem.post();

			cout << sc_time_stamp() << " : P1 = Post 2" << endl;

			// Do a post : increment counter
			sem.post();

			cout << sc_time_stamp() << " : P1 = Post 3" << endl;

			// Do a post : increment counter
			sem.post();

			wait(20, SC_MS);

			cout << sc_time_stamp() << " : P1 = Post 4" << endl;

			// Do a post : increment counter
			sem.post();

		}

	}

	void p2() {

		// Forever loop
		while(true) {

			cout << sc_time_stamp() << " : P2 = Wait ..." << endl;

			// Decrement counter or wait for a post
			sem.wait();

			cout << sc_time_stamp() << " : P2 = Write ..." << endl;

			wait(2, SC_MS);

		}

	}

};

#endif
