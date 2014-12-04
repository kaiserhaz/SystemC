/**
 * PCIX main
 */

/**
 * Includes
 */
#include "pcix_master.h"
#include "pcix_slave.h"

int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(1, SC_NS);

	pcix_master* pcix_m_0 = new pcix_master("pcix_m_0");
	pcix_slave* pcix_s_0 = new pcix_slave("pcix_s_0");
	pcix_bus* pcix_b_0 = new pcix_bus("pcix_b_0");

	pcix_m_0->p_slave(*pcix_b_0);
	pcix_s_0->p_master(*pcix_b_0);

	sc_start();

	system("pause");

	return 0;

}
