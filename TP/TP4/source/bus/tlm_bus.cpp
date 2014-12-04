#include "tlm_bus.h"

/**
 * TLM Bus service implementations
 */

/**
 * Master IF methods
 */

/** Read data from Slave **/

int tlm_bus::read2slave (unsigned int addr_) {
	
	mutex.lock(); // This is a blocking function
	              // Waits till mutex is free

	addr = addr_;
	accesstype = true;

	mutex.unlock();

	rw2slave_ev.notify(SC_ZERO_TIME);

	wait(w2master_ev);

	return data;

}

/** Write data to Slave **/

void tlm_bus::write2slave (unsigned int addr_, int data_) {

	mutex.lock();

	data = data_;
	addr = addr_;
	accesstype = false;
	
	mutex.unlock();

	rw2slave_ev.notify(SC_ZERO_TIME);

	wait(w2slave_ack_ev);

}

/** Return int0 interrupt event **/

const sc_event& tlm_bus::int0_event() const {

	return int0_interrupt;

}

/** Return int1 interrupt event **/

const sc_event& tlm_bus::int1_event() const {

	return int1_interrupt;

}

/**
 * Slave IF methods
 */

/** Return RW event **/

const sc_event& tlm_bus::rw_event() const {

	return rw2slave_ev;

}

/** Return W acknowledge **/

void tlm_bus::w2slave_ack() {

	w2slave_ack_ev.notify(SC_ZERO_TIME);
	
}

/** Return access type **/

const bool tlm_bus::is_read() const {

	return accesstype;

}

/** Gets address **/

const unsigned int tlm_bus::getAddress() const {
	
	return addr;

}

/** Gets data **/

const int tlm_bus::getData () const {

	return data;

}

/** Sends data to master **/

void tlm_bus::senddata2master (int data_) {

	mutex.lock();

	data=data_;

	mutex.unlock();

	w2master_ev.notify(SC_ZERO_TIME);

}

/** Notify int0 **/

void tlm_bus::int0_notify() {

	int0_interrupt.notify(SC_ZERO_TIME);

}

/** Notify int1 **/

void tlm_bus::int1_notify() {

	int1_interrupt.notify(SC_ZERO_TIME);

}
