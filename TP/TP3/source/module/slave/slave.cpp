#include "slave.h"

/**
 * Slave module implementation
 */

void slave::slave_thread(void) {

	while(1) {

		wait(slave::p_master->rw_event());

		cout << " SLAVE: RW event triggered " << endl;

		if(slave::p_master->is_read())
			slave::p_master->senddata2master(slave::memory[slave::p_master->getAddress()]);
		else
			slave::memory[slave::p_master->getAddress()] = slave::p_master->getData();

		cout << " SLAVE: " << "RW event: ";
		cout << "@" << slave::p_master->getAddress() << endl;

		if(slave::p_master->getAddress() == 31) {

			if(slave::p_master->is_read())
				slave::addr_lo_hit.notify(SC_ZERO_TIME);
			else
				slave::addr_hi_hit.notify(SC_ZERO_TIME);

		}
		
			

		slave::p_master->w2slave_ack();

	}

}

void slave::int0_method(void) {

	slave::p_master->int0_notify();

}

void slave::int1_method(void) {

	slave::p_master->int1_notify();

}
