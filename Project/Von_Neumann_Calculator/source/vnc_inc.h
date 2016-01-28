/**
 * VNC Includes
 */

/** Include guard **/
#ifndef VNC_INC_H
#define VNC_INC_H

/** Includes **/
#include <systemc.h>

/** Constants **/
#define SYS_CLOCK            10               // System clock value
#define SYS_CLOCK_UNIT       SC_NS            // System clock value unit

#define MEM_SIZE             1024             // Memory size

#define MEM_ADDR_WORD_LEN 16                  // Memory address word length
#define MEM_DATA_WORD_LEN 16                  // Memory data word length

/** Typedefs **/
typedef sc_lv<MEM_ADDR_WORD_LEN> a_word_t;    // Address word type
typedef sc_lv<MEM_DATA_WORD_LEN> d_word_t;    // Data word type

struct mem_trans {                            // Memory transaction structure

	sc_logic rst_n;                           // Reset signal instance
	sc_logic r_nw;                            // Read/write signal instance
	a_word_t addr;                            // Address line instance
	d_word_t data;                            // Data line instance

	friend ostream& operator<<(ostream& os, const mem_trans& m_t); // Streaming operator

};

/** Operator overloading **/
ostream& operator<<(ostream& os, const mem_trans& m_t) {

	// Concatenate the various signals using string representations
	os << " Command: " << ((m_t.r_nw == SC_LOGIC_1) ? 'W':'R') << "\n";
	os << " Address: @" << m_t.addr << "\n Data:    " << m_t.data.to_string();

	return os;

}

#endif
