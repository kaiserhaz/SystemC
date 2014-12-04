#include "testbench\testbench.h"

int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(1.0, SC_NS);

	testbench test_inst("test_inst");

	sc_start(10, SC_MS);

	system("pause");

	return 0;

}
