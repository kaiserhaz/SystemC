/**
 * 11.7 : Top-level Module
 */

/**
 * Define guard
 */
#ifndef TOP
#define TOP

/**
 * Includes
 */
#include "master.h"
#include "slave.h"

/**
 * Top-level Module Definition
 */
class top : public sc_module {

	//Submodule declarations
	master master_i;
	sc_vector<slave> slave_i;
	int _k;

	public:

	// Constructor
	top( sc_module_name module_name , int k ) :
	sc_module( module_name ) , master_i("master"), slave_i("slave"), _k(k) {

		slave_i.init(N_SLAVE, sc_bind(&top::create_slave, this, sc_unnamed::_1, sc_unnamed::_2));
		
		for(int i=0; i<N_SLAVE; i++) {

			master_i.initiator_port[i].bind(slave_i[i].target_port);

		}

	}
	
	~top() {}

	slave* top::create_slave(const char* name, size_t idx) {
		
		slave* s = new slave(name,_k);

		return s;

	}

};

#endif
