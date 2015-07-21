#include "testbench\testbench.h"

/** This is not exactly a TLM-related implementation. We just used the name to suggest the communication structure **/

int sc_main(int argc, char* argv[]) {

	testbench test_inst("test_inst");

	sc_start();

	system("pause");

	return 0;

}
