/**
 * 10.3.2 : Generator Channel
 */

/**
 * Define guard
 */
#ifndef GENERATOR
#define GENERATOR

/**
 * Includes
 */
#include "generator_if.h"

/**
 * Generator Channel Definition
 */
struct generator: public sc_channel, public generator_if {

	SC_HAS_PROCESS(generator);

	// Constructors
	explicit generator() : sc_channel(sc_gen_unique_name("generator")),
		                   m_period(sc_get_default_time_unit()),
						   m_tick(0)
	{
		
		SC_METHOD(generator_method);
			sensitive << m_clk;

	}

	explicit generator(sc_module_name nm, sc_time _period) : sc_channel(nm),
		                                                     m_period(_period),
															 m_tick(0)
	{

		SC_METHOD(generator_method);
			sensitive << m_clk;

	}

	// User methods
	const sc_event& default_event() const{ return m_clk; }
	const sc_event& posedge_event() const{ return m_clk; }
	const int getTickNumber() const{ return m_tick; }

	// Processes
	void generator_method();

	private:

	sc_event m_clk;
	sc_time m_period;
	int m_tick;

	// Copy constructor so compiler won't create one
	generator( const generator& );

};

#endif
