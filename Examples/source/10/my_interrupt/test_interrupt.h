/**
 * 10.1.6 : my_interrupt Test Scenario
 */

/**
 * Define guard
 */
#ifndef TEST_INTERRUPT
#define TEST_INTERRUPT

/**
 * Includes
 */
#include <systemc.h>
#include "processor.h"
#include "peripheral.h"
#include "my_interrupt.h"
#include "my_interrupt_in_if.h"
#include "my_interrupt_out_if.h"

/**
 * Test Scenario Definition
 */
SC_MODULE( test_interrupt ) {

	my_interrupt* irq;
	processor* processor_i;
	peripheral* peripheral_i;

	SC_HAS_PROCESS(test_interrupt);

	test_interrupt(sc_module_name nm);

};

#endif
