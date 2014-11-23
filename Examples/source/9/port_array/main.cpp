/**
 * 9.3.4 : Port Array Simulation
 */

/**
 * Includes
 */
#include "producer.h"
#include "consumer.h"
#include "broadcast.h"

/**
 * Defines
 */
#define MAX 15

/**
 * main
 */
int sc_main(int argc, char* argv[]) {

	sc_fifo<int> mess_prod[5], mess_broadcast[MAX];

	// Producers Connections
	
	producer *producer_inst[5];

	for(int i=0; i<5; i++) {

		producer_inst[i] = new producer("producer" + i, i);
		producer_inst[i]->mess_out(mess_prod[i]);

	}

	// Broadcast Connections
	broadcast broadcast_inst("broadcast");

	for(int i=0; i<5; i++)
		broadcast_inst.mess_in(mess_prod[i]);

	for(int i=0; i<MAX; i++)
		broadcast_inst.mess_out(mess_broadcast[i]);

	// Consumer Connections
	consumer *consumer_inst[MAX];

	for(int i=0; i<MAX; i++) {

		consumer_inst[i] = new consumer("consumer" + i, i);
		consumer_inst[i]->mess_in(mess_broadcast[i]);

	}

	sc_start(1, SC_MS);

	system("pause");

	return 0;

}
