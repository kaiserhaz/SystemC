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
template< class ADDRESS , class DATA , int N = 1> // N reflects the port 'size';
class basic_initiator_port :                      //  how many slave ports could be connected to it
	public sc_port< tlm_transport_if< basic_request< ADDRESS , DATA > , basic_response<DATA> > , N >,
	public basic_if< ADDRESS , DATA >
{

	public:
		
		// Just to avoid writing that long line, we'll give it a type alias
		typedef tlm_transport_if< basic_request< ADDRESS , DATA > , basic_response<DATA> > if_type;
		
		// Constructor
		basic_initiator_port( const char* port_name ) :
		sc_port< if_type , N > ( port_name ) {}

		// The basic idea here is to:
		//  1) Set the attributes of the request object
		//  2) Collect the response by calling the 'transport' method (using the self-reference pointer)
		//  3) Return the response status
		//
		// The 'transport' method is not a function native to this class, but it is defined inside the tlm_transport_if
		
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
