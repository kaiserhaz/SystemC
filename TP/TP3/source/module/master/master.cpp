#include "master.h"

/**
 * Master module implementation
 */

void master::master_thread(void) {

	for(unsigned i=0; i < 32; i++) {

		master::p_slave->write2slave(i, i+128);

		cout << " MASTER: Writing " << i+128 << " at " << i << endl;

	}

	for(unsigned j=0; j < 32; j++) {

		cout << " MASTER: Data read: " << master::p_slave->read2slave(j);
		cout << " at address " << j << endl;

	}

}

void master::int0_method(void) {

	cout << " MASTER: Write complete " << endl;

}

void master::int1_method(void) {

	cout << " MASTER: Read complete " << endl;

}
