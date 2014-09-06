/**
 * 9.1.3 : Port Simulation
 */

/**
 * Includes
 */
#include "modA.h"
#include "modB.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	sc_fifo<int> fifo1("positive"), fifo2("negative");

	modA modA_inst("modA");
		modA_inst.fifo_o1(fifo1); // by-name
		modA_inst.fifo_o2(fifo2);
		// modA_inst(fifo1, fifo2);

	modB modB_inst("modB");
		// modB_inst.fifo_i1(fifo1);
		// modB_inst.fifo_i2(fifo2);
		modB_inst(fifo2, fifo1); // by-position

	sc_start(10, SC_MS);

	system("pause");

	return 0;

}
