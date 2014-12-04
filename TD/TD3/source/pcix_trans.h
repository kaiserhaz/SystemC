/**
 * PCI Transfer
 */

/**
 * Define guard
 */
#ifndef PCIX_TRANS
#define PCIX_TRANS

/**
 * Includes
 */
#include <systemc.h>

/**
 * PCI Transfer Structure
 */
struct pcix_trans {

	int devnum;
	int addr;
	int attr1;
	int attr2;
	int cmnd;
	int data[8];
	bool done;

	// Constructors
	pcix_trans() : devnum(-1), addr(-1), cmnd(-1), attr1(-1),
		           attr2(-1), done(true)
	{

		for(unsigned i=0; i!=8; i++) data[i] = 0;

	}

	pcix_trans(int _devnum, int _addr, int _attr1, int _attr2,
		       int _cmnd, int* _data, int _done)
			  : devnum(_devnum), addr(_addr), cmnd(_cmnd),
			    attr1(_attr1), attr2(_attr2), done(_done)
	{

		for(unsigned i=0; i!=8; i++) data[i] = _data[i];

	}

	// Required by sc_signal<> and sc_fifo<>
	pcix_trans& operator=(const pcix_trans& rhs);

	// Required by sc_signal<>
	bool operator==(const pcix_trans& rhs) const;

};

// Stream operator to output a PCIX transaction packet to terminal
ostream& operator<<(ostream& file, const pcix_trans& trans);

// Trace a PCIX transaction packet in case it is used in an sc_signal
void sc_trace(sc_trace_file*& tf, const pcix_trans& trans, const std::string nm);

#endif
