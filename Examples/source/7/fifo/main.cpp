/**
 * 7.2.3 : Fifo Simulation
 */

/**
 * Includes
 */
#include "consumer.h"
#include "producer.h"

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	// Instance creation and signal connection
	sc_fifo<int> fifo1, fifo2;

	producer prod0("prod0");
		prod0.fifo_out(fifo1);
		prod0.fifo_in(fifo2);

	consumer cons0("cons0");
		cons0.fifo_out(fifo2);
		cons0.fifo_in(fifo1);

	// Simulation start
	sc_start(100, SC_MS);

	system("pause");

	return 0;

}
