/**
 * 10.3.4 : Test Generator
 */

/**
 * Define guard
 */
#ifndef TEST_GENERATOR
#define TEST_GENERATOR

/**
 * Includes
 */
#include "generator.h"

/**
 * Test Generator Definition
 */
SC_MODULE( test_generator ) {

	sc_port<generator_if> clock;

	SC_CTOR(test_generator) {

		SC_METHOD(test_method);
			sensitive << clock;
			dont_initialize();

	}

	void test_method(void) {

		cout << clock->getTickNumber() << " : Received a tick at ";
		cout << sc_time_stamp() << "." << endl;

	}

};

#endif
