/**
 * 10.1.1 : my_interrupt Input Interface
 */

/**
 * Define guard
 */
#ifndef MY_INTERRUPT_IN_IF
#define MY_INTERRUPT_IN_IF

/**
 * Includes
 */
#include <systemc.h>

/**
 * my_interrupt Input Interface Definition
 */
struct my_interrupt_in_if: public sc_interface
{
	virtual const sc_event& default_event() const= 0;
};

#endif
