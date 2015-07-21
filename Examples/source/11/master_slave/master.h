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

		sc_vector< basic_initiator_port<ADDRESS_TYPE,DATA_TYPE> > initiator_port;

		SC_HAS_PROCESS( master );

		master::master( sc_module_name module_name ) :
		sc_module( module_name ), initiator_port("iport")
		{

			initiator_port.init(N_SLAVE, &master::create_port);

			SC_THREAD( master_thread );

		}

		master::~master() {}

		void master_thread() {

			DATA_TYPE d = 0;
			unsigned int i = 0, s = 0;

			for ( ADDRESS_TYPE a = 0; a < 64; a++ ) {

				cout << "MASTER: Writing Address " << a << " @ " << initiator_port[i].name();
				cout << " value " << a + 10 << endl;

				initiator_port[i++].write( a , a + 10 );

				if(i > N_SLAVE-1) i %= N_SLAVE;

			}

			i = 0;

			for( ADDRESS_TYPE a = 0; a < 64; a++ ) {

				if(s) {

					cout << "MASTER: Read Address " << a << " @ " << initiator_port[i].name() << " got " << d << endl;

					initiator_port[i++].read( a , d );

				}
				else {

					cout << "MASTER: Writing Address " << a << " @ " << initiator_port[i].name();
					cout << " value " << a + 10 << endl;

					initiator_port[i++].write( a , a + 10 );

				}

				s = (unsigned int)(rand() % 2);
				if(i > N_SLAVE-1) i %= N_SLAVE;

			}

		}

	static basic_initiator_port<ADDRESS_TYPE,DATA_TYPE>* master::create_port(const char* name, size_t idx){
		
		return new basic_initiator_port<ADDRESS_TYPE,DATA_TYPE>(name);
	
	}

};

#endif
