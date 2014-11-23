/**
 * 10.1.7 : my_interrupt Test Scenario Implementation
 */

/**
 * Includes
 */
#include "test_interrupt.h"

test_interrupt::test_interrupt(sc_module_name nm) {

	irq = new my_interrupt();
	processor_i = new processor("processor_i");
	peripheral_i = new peripheral("peripheral_i");

	processor_i->irq(*irq);
	peripheral_i->irq(*irq);

}
