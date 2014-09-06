/**
 * 7.4.1 : Signal Resolved Definition
 */

/**
 * Define guard
 */
#ifndef SIGNAL_RESOLVED_H
#define SIGNAL_RESOLVED_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * Signal Definition
 */

SC_MODULE( signal_resolved ) {

	//sc_signal<bool> sig; // Channel
	sc_signal_resolved sig; // Resolved channel

	SC_CTOR( signal_resolved ) {
		
		SC_THREAD(writer);
		SC_THREAD(reader);
		SC_METHOD(writer2);
			sensitive << sig.posedge_event(); // Sensitive to the pos edge event
	}

	void writer() {

		wait(50, SC_NS);

		//sig.write(false);
		//sig.write(true);
		sig.write(SC_LOGIC_0);
		sig.write(SC_LOGIC_1);

		wait(50, SC_NS);

		//sig = false; // Calls operator= ( const T& )
		sig = SC_LOGIC_0;
	}

	void reader() {

		wait(sig.value_changed_event());
		
		//bool i = sig.read(); // Reads true
		sc_logic i = sig.read();
		cout << " Signal received is : " << i << endl;

		wait(sig.value_changed_event());
		
		i = sig; // Calls operator const T& () which returns false
		cout << " Signal received again is : " << i << endl;
	}

	void writer2() {

		//sig.write(!sig.read()); // An error. A signal shall not have multiple writers
		(sc_logic)sig ^= (sc_logic)sig; // sc_signal_resolved doesn't overwrite the !() operator, therefore we cast to sc_logic
	}

};

#endif
