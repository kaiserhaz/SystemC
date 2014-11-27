/**
 * 11.6 : TLM1 Example
 */

/**
 * Includes
 */
#include "master.h"
#include "slave.h"

int sc_main(int argc, char** argv) {

	master master_i("master");
	slave slave_i("slave",4);

	master_i.initiator_port( slave_i.target_port );

	sc_start();

	system("pause");

	return 0;

}
