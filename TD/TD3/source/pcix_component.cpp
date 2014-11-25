/**
 * 10.2.4 : PCI Component Implementation
 */

/**
 * Includes
 */
#include "pcix_component.h"

void pcix_component::send_pcix_packet_thread(void) {
	
	const unsigned ii = rand()%50;

	pcix_trans* pcix_data = new pcix_trans[ii];

	for(unsigned i=0; i<ii; i++) {

		pcix_data[i].cmnd = rand();
		pcix_data[i].attr1 = rand();
		pcix_data[i].attr2 = rand();
		pcix_data[i].devnum = rand();
		pcix_data[i].addr = rand();
		
		for(unsigned j=0; j<8; j++)
			pcix_data[i].data[j] = rand();

		pcix_data[i].done = (rand()%2)?true:false;
	
	}

	for(unsigned i=0; i<ii; i++) {

		pcix_component::pcix_sig = pcix_data[i];
		pcix_component::pcix_fifo.write(pcix_data[i]);

		wait(2, SC_NS);

	}

}

void pcix_component::receive_pcix_packet_method(void) {

	cout << sc_time_stamp() << " New PCIX transaction " << pcix_component::pcix_sig << endl;

}
