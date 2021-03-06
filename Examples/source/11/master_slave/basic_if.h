/**
 * 11.1 : Basic Interface
 */

/**
 * Define guard
 */
#ifndef BASIC_IF
#define BASIC_IF

#define SC_INCLUDE_DYNAMIC_PROCESSES

/**
 * Includes
 */
#include <systemc>
#include <tlm>

using namespace std;
using namespace tlm;
using namespace sc_core;

typedef unsigned int ADDRESS_TYPE;
typedef unsigned int DATA_TYPE;
#define N_SLAVE 5

/** Basic request types to indicate the nature of the request **/
enum basic_request_type
{
  READ , WRITE
};

/** Basic status to indicate the status of the communication **/
enum basic_status
{
  ERROR , SUCCESS
};

/** Basic request object description **/
template< typename ADDRESS_TYPE , typename DATA_TYPE >
class basic_request
{
public:
  basic_request_type type;

  ADDRESS_TYPE &get_address() { return a; } // makes it routable

  ADDRESS_TYPE a;
  DATA_TYPE d;

};

/** Basic response object description **/
template< typename DATA_TYPE >
class basic_response
{
public:
  basic_response() : status( ERROR ) {} // makes it routable

  basic_request_type type;
  basic_status status;

  DATA_TYPE d;

};

/**
 * Basic Interface Definition
 */
template< typename ADDRESS_TYPE , typename DATA_TYPE >
class basic_if
{

	public:

		virtual basic_status write( const ADDRESS_TYPE &a , const DATA_TYPE &d ) = 0;
		virtual basic_status read( const ADDRESS_TYPE &a , DATA_TYPE &d ) = 0;

};

/** Helper functions, or rather, operator definitions **/
template< typename ADDRESS_TYPE , typename DATA_TYPE >
ostream &operator<<( ostream &fsout ,
                     const basic_request<ADDRESS_TYPE,DATA_TYPE> &req ) {

  switch( req.type )
  {
  case READ :
    fsout << "Read Request : address = " << req.a << endl;
    break;
  case WRITE :
    fsout << "Write Request : address,data =  " << req.a << " , " << req.d << endl;
    break;
  default :
    fsout << "Error : no request type" << endl;
    break;
  }

  return fsout;
}

template< typename DATA_TYPE >
ostream &operator<<( ostream &fsout ,
                     const basic_response<DATA_TYPE> &req ) {

  if( req.status == ERROR ) {
    fsout << "Error Response" << endl;
    return fsout;
  }
  
  switch( req.type )
  {
  case READ :
    fsout << "Successful Read Response : data = " << req.d << endl;
    break;
  case WRITE :
    fsout << "Successful Write Response" << endl;
    break;
  default :
    fsout << "Error : no request type ( in response )" << endl;
    break;
  }

  return fsout;

}

template< typename ADDRESS_TYPE , typename DATA_TYPE >
bool operator==( const basic_request<ADDRESS_TYPE,DATA_TYPE> &req1 ,
                 const basic_request<ADDRESS_TYPE,DATA_TYPE> &req2 )
{
  if( req1.type != req2.type ) {
    return false;
  }  
  
  if( req1.a != req2.a ) {
    return false;
  } 
 
  if( req1.type == WRITE && req1.d != req2.d ) {
     return false;
  }
  
  return true;

}

template< typename ADDRESS_TYPE , typename DATA_TYPE >
bool operator!=( const basic_request<ADDRESS_TYPE,DATA_TYPE> &req1 ,
                 const basic_request<ADDRESS_TYPE,DATA_TYPE> &req2 ) {
                    
  return !(req1 == req2);                    
}

#endif
