/**
 * 11.3 : Basic Slave Base
 */

/**
 * Define guard
 */
#ifndef BASIC_SLAVE_BASE
#define BASIC_SLAVE_BASE

/**
 * Includes
 */
#include "basic_if.h"

/**
 * Basic Slave Base Definition
 */
template< class ADDRESS_TYPE , class DATA_TYPE >
class basic_slave_base :
	public virtual basic_if< ADDRESS_TYPE , DATA_TYPE > ,
	public virtual tlm_transport_if< basic_request< ADDRESS_TYPE , DATA_TYPE > , basic_response<DATA_TYPE> >
{

	public:

		typedef tlm_transport_if< basic_request< ADDRESS_TYPE , DATA_TYPE > , basic_response<DATA_TYPE> > if_type;

		/* Transport Implementation */
		basic_response<DATA_TYPE> transport(const basic_request<ADDRESS_TYPE,DATA_TYPE> &request )
		{

			basic_response<DATA_TYPE> response;

			switch( request.type ) {

				case READ : response.status = read( request.a , response.d );
					        break;
				case WRITE: response.status = write( request.a , request.d );
					        break;
				default: response.status = ERROR;
					     break;

			}

			return response;

		}

};

#endif
