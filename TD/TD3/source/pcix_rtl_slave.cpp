/**
 * PCI RTL Slave Implementation
 */

/**
 * Includes
 */
#include "pcix_rtl_slave.h"

void pcix_rtl_slave::pcix_slave_thread(void) {

	while(1) {

		wait(int_ev);

		cout << " SLAVE: Command received " << endl;

		if(p_cmnd->read() == 0x110) { // Read

			cout << " SLAVE: Received READ request " << endl;

			cout << " SLAVE: Read at @" << p_addr->read() << endl;

			for(unsigned i=0; i<8; i++)
				p_dataout[i]->write(memory[p_addr->read()][i]);

		}
		else if(p_cmnd->read() == 0x111) { // Write

			cout << " SLAVE: Received WRITE request " << endl;

			cout << " SLAVE: Write at @" << p_addr->read() << endl;

			for(unsigned i=0; i<8; i++)
				memory[p_addr->read()][i] = p_datain[i]->read();

		}
		else {

			cout << " SLAVE: Command not supported " << endl;

		}

		wait(10, SC_NS);

		p_rtl2tlm->notify(sc_time(1, SC_NS));

	}

}

void pcix_rtl_slave::rtl2tlm_int(void) {

	int_ev.notify(SC_ZERO_TIME);

	cout << " SLAVE: IRQ line triggered " << endl;

}
