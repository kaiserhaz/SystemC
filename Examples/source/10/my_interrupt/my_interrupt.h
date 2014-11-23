/**
 * 10.1.3 : my_interrupt Channel
 */

/**
 * Define guard
 */
#ifndef MY_INTERRUPT
#define MY_INTERRUPT

/**
 * Includes
 */
#include <systemc.h>
#include "my_interrupt_in_if.h"
#include "my_interrupt_out_if.h"

/**
 * my_interrupt Channel Definition
 */
struct my_interrupt: public sc_prim_channel, public my_interrupt_in_if, public my_interrupt_out_if
{
	// Constructors
	explicit my_interrupt() : sc_prim_channel(sc_gen_unique_name("my_interrupt"))
	{}

	explicit my_interrupt(sc_module_name nm) : sc_prim_channel(nm)
	{}

	void notify() { m_interrupt.notify(); }

	void notify(sc_time t) { m_interrupt.notify(t); }

	const sc_event& default_event() const { return m_interrupt; }

	private:

	sc_event m_interrupt;

	// Copy constructor so compiler won't create one
	my_interrupt( const my_interrupt& );

};

#endif
