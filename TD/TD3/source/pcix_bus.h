/**
 * PCIX Bus Channel
 */

/**
 * Define guard
 */
#ifndef PCIX_BUS
#define PCIX_BUS

/**
 * Includes
 */
#include "pcix_bus_master_if.h"
#include "pcix_bus_slave_if.h"

/**
 * PCIX Bus Interface Definition
 */
struct pcix_bus: public sc_prim_channel, public pcix_bus_master_if,
	             public pcix_bus_slave_if
{

	// Constructors
	explicit pcix_bus() : sc_prim_channel(sc_gen_unique_name("pcix_bus"))
	{ trans = new pcix_trans; }

	explicit pcix_bus(sc_module_name nm) : sc_prim_channel(nm)
	{ trans = new pcix_trans; }

	// Interface methods

	//// Master

	void send_transaction(pcix_trans _trans);
	bool write(int _addr, int* _data, int _length);
	bool read(int _addr, int* _data, int _length);

	//// Slave

	void receive_transaction(pcix_trans& _trans);
	const sc_event& transaction_event(void) const;
	pcix_trans get_transaction(void);
	void transaction_done(pcix_trans _trans);

	private:

		sc_mutex trans_mutex;
		sc_event trans_ev;
		sc_event trans_done_ev;
		pcix_trans* trans;

};

#endif
