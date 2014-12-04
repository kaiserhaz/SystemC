/**
 * 10.1.2 : my_interrupt Output Interface
 */

/**
 * Define guard
 */
#ifndef MY_INTERRUPT_OUT_IF
#define MY_INTERRUPT_OUT_IF

/**
 * Includes
 */
#include <systemc.h>

/**
 * my_interrupt Output Interface Definition
 */
struct my_interrupt_out_if: public sc_interface
{
	virtual void notify() = 0;
	virtual void notify(sc_time t) = 0;
};

#endif
