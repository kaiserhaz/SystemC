/**
 * PCIX TLM2RTL Bus Adaptor Implementation
 */

/**
 * Includes
 */
#include "tlm2rtl_bus.h"

void tlm2rtl_bus::tlm2rtl_thread(void) {
	
	pcix_trans local;

	while(1) {

		local = p_master->get_transaction();

		cout << " TRANSACTOR: Transaction event " << endl;

		if(local.cmnd == 0x110) { // Read

			cout << " TRANSACTOR: READ request " << endl;

			local = rtl_read(local);

		}
		else if(local.cmnd == 0x111) { // Write

			cout << " TRANSACTOR: WRITE request " << endl;

			rtl_write(local);

		}
		else {

			cout << " TRANSACTOR: Command not supported " << endl;

		}

		p_master->transaction_done(local);

	}

}

void tlm2rtl_bus::tlm2rtl_int(void) {

	int_ev.notify(SC_ZERO_TIME);

	cout << " TRANSACTOR: IRQ line triggered " << endl;

}

/** Helper functions **/

void tlm2rtl_bus::rtl_write(pcix_trans _trans) {

	rtl_mutex.lock();

	p_devnum->write(_trans.devnum);
	p_addr->write(_trans.addr);

	wait(20, SC_NS);

	p_attr1->write(_trans.attr1);
	p_attr2->write(_trans.attr2);
	p_cmnd->write(_trans.cmnd);

	wait(30, SC_NS);

	for(int i=0; i<8; i++)
		p_dataout[i]->write(_trans.data[i]);

	wait(80, SC_NS);

	rtl_mutex.unlock();

	p_tlm2rtl->notify(SC_ZERO_TIME);
	
}

pcix_trans tlm2rtl_bus::rtl_read(pcix_trans __trans) {

	pcix_trans _trans;

	rtl_mutex.lock();

	p_devnum->write(__trans.devnum);
	p_addr->write(__trans.addr);

	wait(20, SC_NS);

	p_attr1->write(__trans.attr1);
	p_attr2->write(__trans.attr2);
	p_cmnd->write(__trans.cmnd);

	wait(30, SC_NS);

	rtl_mutex.unlock();
	
	p_tlm2rtl->notify(SC_ZERO_TIME);

	wait(int_ev);
	
	rtl_mutex.lock();

	_trans.devnum = p_devnum->read();
	_trans.addr = p_addr->read();
	_trans.attr1 = p_attr1->read();
	_trans.attr2 = p_attr2->read();
	_trans.cmnd = p_cmnd->read();

	for(int i=0; i<8; i++)
		_trans.data[i] = p_datain[i]->read();

	wait(5, SC_NS);

	rtl_mutex.unlock();

	return _trans;

}
