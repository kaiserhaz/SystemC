#include <systemc.h>
#include "tlm_bus.h"

/**
 * TLM Bus service implementations
 */

/** Read data from Slave **/

int tlm_bus::read2slave (unsigned int addr_) {
	
	mutex.lock();

	addr = addr_;
	accesstype = true;

	rw2slave_ev.notify();

	mutex.unlock();

	wait(w2master_ev);

	return data;

}

void tlm_bus::write2slave (unsigned int addr_, int data_) {

	mutex.lock();
	data=data_;
	addr=addr_;
	accesstype=false;
	rw2slave_ev.notify();
	mutex.unlock();

}

const sc_event& tlm_bus::int0_event() {

	return  int0_interrupt;

}

const sc_event& tlm_bus::int1_event() {

	return int1_interrupt;

}

const sc_event& tlm_bus::rw_event() {

	return rw2slave_ev;

}

const bool tlm_bus::is_read() const {

	return accesstype;

}
	
const unsigned int tlm_bus::getAddress() const {
	
	return addr;

}

const int tlm_bus::getData () const {

	return data;

}

void tlm_bus::senddata2master (int data_) {

	mutex.lock();
	data=data_;
	w2master_ev.notify();
	mutex.unlock();

}

void tlm_bus ::int0_notify() {

	return int0_interrupt.notify();

}

void tlm_bus ::int1_notify() {

	return int1_interrupt.notify();

}