/**
 * 7.3.1 : Signal Definition
 */

/**
 * Define guard
 */
#ifndef SIGNAL_H
#define SIGNAL_H

/**
 * Includes
 */
#include <systemc.h>
#include <string.h>

/**
 * Signal Definition
 */

SC_MODULE( signal ) {

	enum color {BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE};

	/** Signal fields **/
	int count;
	color traffic_temp;
	std::string message_temp;

	sc_signal<int> count_sig;
	sc_signal<color> traffic_sig;
	sc_signal<std::string> message_sig;

	/** Signal Contructor **/
	SC_CTOR( signal ) {

		// Thread declaration
		SC_THREAD(P1_thread);
		SC_METHOD(P2_method);
			sensitive << count_sig << traffic_sig << message_sig;
			dont_initialize();
	}

	/** Signal Methods **/
	void P1_thread(void);
	void P2_method(void);

};

#endif
