/**
 * 10.3.3 : Generator Channel Implementation
 */

/**
 * Includes
 */
#include "generator.h"

void generator::generator_method(void) {

	generator::m_tick++;
	generator::m_clk.notify(generator::m_period);

}
