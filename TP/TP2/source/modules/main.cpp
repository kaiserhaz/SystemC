#include <systemc.h>
#include "../testbench/benches.h"

int sc_main(int argc, char* argv[])
{
	//test_clk_unit();
	//test_tx_unit();
	//test_rx_unit();
	test_miniuart();
	system("pause");
	return 0;
}