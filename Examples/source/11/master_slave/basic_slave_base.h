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
template< class ADDRESS_TYPE , class DATA_TYPE > // This is a purely virtual class, meaning that it will be implemented
class basic_slave_base :                         //  and the object that will implement it will be the slave (i.e. slave
	public virtual basic_if< ADDRESS_TYPE , DATA_TYPE > , // inherits this class
	public virtual tlm_transport_if< basic_request< ADDRESS_TYPE , DATA_TYPE > , basic_response<DATA_TYPE> >
{

	public:

		// Avoid typing all this stuff by using a type alias
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
