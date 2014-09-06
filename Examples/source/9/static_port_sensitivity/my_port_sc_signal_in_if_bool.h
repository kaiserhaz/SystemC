/**
 * 9.2.1 : MyPort Structure
 */

/**
 * Define guard
 */
#ifndef MYPORT_H
#define MYPORT_H

/**
 * Includes
 */
#include <systemc.h>

/**
 * MyPort Event Finder
 */
struct my_port_sc_signal_in_if_bool : public sc_port< sc_signal_in_if<bool> > {

	typedef sc_signal_in_if<bool> if_type; // typing aid

	sc_event_finder& ef_posedge_event() const {

		return *new sc_event_finder_t<if_type> (*this, &if_type::posedge_event);
	
	}

};

#endif
