/**
 * 11.5 : Slave Module
 */

/**
 * Define guard
 */
#ifndef SLAVE
#define SLAVE

/**
 * Includes
 */
#include "basic_slave_base.h"

/**
 * Slave Module Definition
 */
class slave : public sc_module , public virtual basic_slave_base< ADDRESS_TYPE , DATA_TYPE >
{
	
	public:

		sc_export<if_type> target_port;

		// Constructor
		slave( sc_module_name module_name , int k ) :
		sc_module( module_name ) , target_port("iport") {

			target_port.bind(*this);
			memory = new ADDRESS_TYPE[ k * 1024 ];

		}
		
		basic_status slave::write( const ADDRESS_TYPE &a , const DATA_TYPE &d ) {

			cout << name() << " writing at " << a << " value " << d << endl;
			
			memory[a] = d;

			return SUCCESS;

		}

		basic_status slave::read( const ADDRESS_TYPE &a , DATA_TYPE &d ) {

			d = memory[a];

			cout << name() << " reading from " << a << " value " << d << endl;

			return SUCCESS;

		}

		private:

			ADDRESS_TYPE *memory;

};

#endif
