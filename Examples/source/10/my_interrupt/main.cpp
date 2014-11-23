/**
 * 10.1.8 : my_interrupt main
 */

/**
 * Includes
 */
#include <systemc.h>
#include "test_interrupt.h"

int sc_main(int argc, char* argv[]) {

	cout << " INFO: Elaborating " << endl;

	test_interrupt interrupt_i("interrupt_i");
	
	cout << " INFO: Simulating " << endl;

	sc_start();

	cout << " INFO: Post-processing " << endl;

	system("pause");

	return 0;

}
