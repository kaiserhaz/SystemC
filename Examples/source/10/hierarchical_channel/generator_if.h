/**
 * 10.3.1 : Generator Interface
 */

/**
 * Define guard
 */
#ifndef GENERATOR_IF
#define GENERATOR_IF

/**
 * Includes
 */
#include <systemc.h>

/**
 * Generator Interface Definition
 */
struct generator_if: public sc_interface {

	virtual const sc_event& default_event() const= 0;
	virtual const sc_event& posedge_event() const= 0;
	virtual const int getTickNumber() const= 0;

};

#endif
