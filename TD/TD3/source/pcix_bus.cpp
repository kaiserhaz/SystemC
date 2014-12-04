/**
 * PCIX Bus Channel
 */

/**
 * Includes
 */
#include "pcix_bus.h"

/**
 * PCIX Bus Interface Implementation
 */

//// Master

void pcix_bus::send_transaction(pcix_trans _trans) { // Transport layer API

	trans_mutex.lock();

	*trans = _trans;

	trans_mutex.unlock();

	trans_ev.notify(SC_ZERO_TIME);

	wait(trans_done_ev);

}

bool pcix_bus::write(int _addr, int* _data, int _length) { // Message layer API

	if(trans->done) {

		pcix_trans new_trans;

		new_trans.addr = _addr;
		new_trans.attr1 = rand();
		new_trans.attr2 = rand();
		new_trans.cmnd = 0x0111;

		for(int i=0; i<_length; i++) {

			if(i < 8)
				new_trans.data[i] = _data[i];

		}

		new_trans.devnum = rand();

		new_trans.done = false;

		send_transaction(new_trans);

		return true;

	}
	else
		return false;

}

bool pcix_bus::read(int _addr, int* _data, int _length) { // Message layer API
	
	if(trans->done) {

		pcix_trans new_trans;

		new_trans.addr = _addr;
		new_trans.attr1 = rand();
		new_trans.attr2 = rand();
		new_trans.cmnd = 0x0110;
	
		new_trans.devnum = rand();

		new_trans.done = false;

		send_transaction(new_trans);

		for(int i=0; i<_length; i++)
			_data[i] = trans->data[i];

		return true;

	}
	else
		return false;

}

	//// Slave

void pcix_bus::receive_transaction(pcix_trans& _trans) { // Transport layer API

	wait(trans_ev);

	trans_mutex.lock();

	_trans = *trans;

	trans_mutex.unlock();

}

const sc_event& pcix_bus::transaction_event(void) const {

	return trans_ev;

}

pcix_trans pcix_bus::get_transaction(void) { // Message layer API

	pcix_trans _trans;

	receive_transaction(_trans);

	return _trans;

}

void pcix_bus::transaction_done(pcix_trans _trans) { // Transport layer API

	trans_mutex.lock();

	*trans = _trans;

	trans->done = true;

	trans_mutex.unlock();

	trans_done_ev.notify(SC_ZERO_TIME);

}