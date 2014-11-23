/**
 * 10.3.5 : Generator main
 */

/**
 * Includes
 */
#include "test_generator.h"

int sc_main(int argc, char* argv[]) {

	cout << "INFO: Elaborating ..." << endl;

	sc_set_time_resolution(100,SC_PS);

	sc_time period(2,SC_NS);

	generator clock("clock", period);
	test_generator test_generator_i("test_generator_i");
		test_generator_i.clock(clock);

	cout << "INFO: Simulating " << endl;

	sc_start(20, SC_NS);
	
	cout << "INFO: Post-processing ... " << endl;

	system("pause");

	return 0;

}
