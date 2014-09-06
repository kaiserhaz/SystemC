/**
 * 3.2.1 : MBus Structure
 */

/**
 * Define guard
 */
#ifndef MBUS_H
#define MBUS_H

/**
 * Includes
 */
#include <systemc.h>
#include <string>

/**
 * Constants
 */
const int ADDR_WIDTH = 8; // /!\ A width of 20 takes a whole night to simulate on Intel Celeron!
const int DATA_WIDTH = 8;

/**
 * MBus Structure Definition
 */
struct mbus {

	/** MBus fields **/
	sc_uint<ADDR_WIDTH> address; // Address
	sc_uint<DATA_WIDTH> data;    // Data
	bool read, write;            // Read, Write status

	/** MBus overloaded operators **/
	mbus& operator= (const mbus&);        // Affect operator
	bool  operator== (const mbus&) const; // Equality test operator

};

/**
 * Affect operator implementation
 */
inline mbus& mbus::operator= (const mbus& arg) {

	// Basically, affect the fields of the argument MBus to the current object's fields
	//  and return the current object

	address = arg.address;
	data = arg.data;
	read = arg.read;
	write = arg.write;

	return *this;

}

/**
 * Equality test operator implementation
 */
inline bool mbus::operator== (const mbus& arg) const {

	// Basically, test all of the argument's fields with the current object's field
	//  and return the AND of the tests

	return(	(address == arg.address) &&
			(data == arg.data)       &&
			(read == arg.read)       &&
			(write == arg.write)        );

}

/**
 * Streaming operator overloading
 */
inline ostream& operator<< (ostream& os, const mbus& arg) {

	// Return the concatenated ostream object after appending the argument's
	//  fields in the stream

	os << " address = " << arg.address << "\n" <<
	      " data    = " << arg.data    << "\n" <<
		  " read    = " << arg.read    << "\n" <<
	      " write   = " << arg.write;

	return os;

}

/**
 * sc_trace method overloading
 */
inline void sc_trace (sc_trace_file *tf, const mbus& arg, const std::string& name) {
	
	// Basically, trace each field in the tracefile (when applicable)

	sc_trace (tf, arg.address, name+".address");
	sc_trace (tf, arg.data, name+".data");
	sc_trace (tf, arg.read, name+".read");
	sc_trace (tf, arg.write, name+".write");

}

#endif
