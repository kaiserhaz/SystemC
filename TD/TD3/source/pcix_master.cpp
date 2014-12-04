/**
 * PCI Master Implementation
 */

/**
 * Includes
 */
#include "pcix_master.h"

void pcix_master::pcix_master_thread(void) {
	
	const unsigned int l_send=8, l_recv=8;
	int* send_data = new int[l_send];
	int* recv_data = new int[l_recv];
	int addr = rand()%256;
		
	for(unsigned j=0; j<l_send; j++)
		send_data[j] = rand()%1024;

	cout << " MASTER: Writing data to Slave " << endl;

	while(!p_slave->write(addr, send_data, l_send));

	cout << " MASTER: Reading data from Slave " << endl;

	while(!p_slave->read(addr, recv_data, l_recv));

	cout << "  ";

	for(unsigned i=0; i<8; i++) {

		cout << recv_data[i];

		if(i == 7)
			cout << endl;
		else
			cout << ".";

	}

}
