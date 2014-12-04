/**
 * PCI Slave Implementation
 */

/**
 * Includes
 */
#include "pcix_slave.h"

void pcix_slave::pcix_slave_thread(void) {
	
	pcix_trans local;

	while(1) {

		local = p_master->get_transaction();

		cout << " SLAVE: Transaction event " << endl;

		if(local.cmnd == 0x110) { // Read

			cout << " SLAVE: Received READ request " << endl;

			cout << " SLAVE: Read at @" << local.addr << endl;

			for(unsigned i=0; i<8; i++)
				local.data[i] = memory[local.addr][i];

		}
		else if(local.cmnd == 0x111) { // Write

			cout << " SLAVE: Received WRITE request " << endl;

			for(unsigned i=0; i<8; i++)
				memory[local.addr][i] = local.data[i];

			cout << " SLAVE: Write at @" << local.addr << endl;

		}
		else {

			cout << " SLAVE: Command not supported " << endl;

		}

		p_master->transaction_done(local);

	}

}
