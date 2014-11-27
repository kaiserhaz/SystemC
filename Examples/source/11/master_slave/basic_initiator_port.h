/**
 * 11.2 : Basic Initiator Port
 */

/**
 * Define guard
 */
#ifndef BASIC_INITIATOR_PORT
#define BASIC_INITIATOR_PORT

/**
 * Includes
 */
#include "basic_if.h"

/**
 * Basic Interface Definition
 */
template< class ADDRESS , class DATA , int N = 1>
class basic_initiator_port :
	public sc_port< tlm_transport_if<basic_request< ADDRESS , DATA > , basic_response<DATA> > , N> ,
	public basic_if< ADDRESS , DATA >
{

	public:
		
		typedef tlm_transport_if< basic_request< ADDRESS , DATA > , basic_response<DATA> > if_type;
		
		// Constructor
		basic_initiator_port( const char* port_name ) :
		sc_port< if_type , N > ( port_name ) {}

		virtual basic_status write( const ADDRESS &a , const DATA &d ) {

			basic_request<ADDRESS,DATA> req;
			basic_response<DATA> rsp;

			req.type = WRITE;
			req.a = a;
			req.d = d;
			rsp = (*this)->transport( req );

			return rsp.status;

		}

		virtual basic_status read( const ADDRESS &a , DATA &d ) {

			basic_request<ADDRESS,DATA> req;
			basic_response<DATA> rsp;

			req.type = READ;
			req.a = a;
			rsp = (*this)->transport( req );
			d = rsp.d;

			return rsp.status;

		}

};

#endif
