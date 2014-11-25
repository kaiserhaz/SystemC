/**
 * 10.2.2 : PCI Transfer Implementation
 */

/**
 * Includes
 */
#include "pcix_trans.h"

// Required by sc_signal<> and sc_fifo<>
pcix_trans& pcix_trans::operator= (const pcix_trans& rhs) {

	devnum = rhs.devnum;
	addr = rhs.addr;
	attr1 = rhs.attr1;
	attr2 = rhs.attr2;
	cmnd = rhs.cmnd;

	for(unsigned i=0; i!=8; i++)
		data[i] = rhs.data[i];

	done = rhs.done;

	return *this;

}

// Required by sc_signal<>
bool pcix_trans::operator== (const pcix_trans& rhs) const {

	return(devnum == rhs.devnum && addr == rhs.addr &&
		   attr1 == rhs.attr1 && attr2 == rhs.attr2 &&
		   cmnd == rhs.cmnd && data[0] == rhs.data[0] &&
		   data[1] == rhs.data[1] && data[2] == rhs.data[2] &&
		   data[3] == rhs.data[3] && data[4] == rhs.data[4] &&
		   data[5] == rhs.data[5] && data[6] == rhs.data[6] &&
		   data[7] == rhs.data[7] && done == rhs.done);

}

// Print a PCIX transaction packet out to a stream (usually just the terminal
// window), in a nice-looking format
ostream& operator<<(ostream& os, const pcix_trans& trans) {

	os << "{" << endl;
	os << "cmnd: " << trans.cmnd << ", ";
	os << "attr1: " << trans.attr1 << ", ";
	os << "attr2: " << trans.attr2 << ", " << endl;
	os << "devnum: " << trans.devnum << ", ";
	os << "addr: " << trans.addr << ", " << endl;
	os << "data: " << trans.data[0] << ".";
	os << trans.data[1] << ".";
	os << trans.data[2] << ".";
	os << trans.data[3] << ".";
	os << trans.data[4] << ".";
	os << trans.data[5] << ".";
	os << trans.data[6] << ".";
	os << trans.data[7] << ", " << endl;
	os << "done: " << (trans.done?"true":"false") << endl << "}";

	return os;

}

// Trace function, only required if actually used
void sc_trace(sc_trace_file*& tf, const pcix_trans& trans, const std::string nm) {

	sc_trace(tf, trans.devnum, nm + ".devnum");
	sc_trace(tf, trans.addr, nm + ".addr");
	sc_trace(tf, trans.attr1, nm + ".attr1");
	sc_trace(tf, trans.attr2, nm + ".attr2");
	sc_trace(tf, trans.cmnd, nm + ".cmnd");
	sc_trace(tf, trans.data[0], nm + ".data[0]");
	sc_trace(tf, trans.data[1], nm + ".data[1]");
	sc_trace(tf, trans.data[2], nm + ".data[2]");
	sc_trace(tf, trans.data[3], nm + ".data[3]");
	sc_trace(tf, trans.data[4], nm + ".data[4]");
	sc_trace(tf, trans.data[5], nm + ".data[5]");
	sc_trace(tf, trans.data[6], nm + ".data[6]");
	sc_trace(tf, trans.data[7], nm + ".data[7]");
	sc_trace(tf, trans.done, nm + ".done");

}
