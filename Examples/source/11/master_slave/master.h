/**
 * 11.4 : Master Module
 */

/**
 * Define guard
 */
#ifndef MASTER
#define MASTER

/**
 * Includes
 */
#include "basic_initiator_port.h"

/**
 * Master Module Definition
 */
class master : public sc_module {

	public:

		basic_initiator_port<ADDRESS_TYPE,DATA_TYPE> initiator_port;

		SC_HAS_PROCESS( master );

		master::master( sc_module_name module_name ) :
		sc_module( module_name ), initiator_port("iport")
		{

			SC_THREAD( master_thread );

		}

		void master_thread() {

			DATA_TYPE d;

			for ( ADDRESS_TYPE a = 0; a < 25; a++ ) {

				cout << "Writing Address " << a << " value " << a + 10 << endl;

				initiator_port.write( a , a + 10 );

			}

			for( ADDRESS_TYPE a = 0; a < 25; a++ ) {

				initiator_port.read( a , d );

				cout << "Read Address " << a << " got " << d << endl;

			}

		}

};

#endif
