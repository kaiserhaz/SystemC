#include "testbench\testbench.h"

int sc_main(int argc, char* argv[]) {

	testbench test_inst("test_inst");

	sc_start();

	system("pause");

	return 0;

}
