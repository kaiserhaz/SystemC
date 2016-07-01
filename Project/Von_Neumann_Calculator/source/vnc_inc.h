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
#define SYS_CLOCK_UNIT       SC_NS            // System clock unit

#define MEM_SIZE             65536            // Memory size

#define MEM_ADDR_WORD_LEN    16               // Memory address word length
#define MEM_DATA_WORD_LEN    16               // Memory data word length

#define MEM_DELAY            4                // Memory delay value
#define MEM_DELAY_UNIT       SC_NS            // Memory delay unit

/** Typedefs **/
typedef sc_bv<MEM_ADDR_WORD_LEN> a_word_t;    // Address word type
typedef sc_bv<MEM_DATA_WORD_LEN> d_word_t;    // Data word type

struct mem_trans {                            // Memory transaction structure

	bool     rst_n;                           // Reset signal instance
	bool     r_nw;                            // Read/write signal instance
	a_word_t addr;                            // Address line instance
	d_word_t data;                            // Data line instance

	friend ostream& operator<<(ostream& os, const mem_trans& m_t); // Streaming operator

};

/** Operator overloading **/
ostream& operator<<(ostream& os, const mem_trans& m_t) {

	// Concatenate the various signals using string representations
	os << " Command: " << (m_t.r_nw ? 'W':'R') << "\n";
	os << " Address: @" << std::hex << m_t.addr.to_uint() << "\n Data:    " << m_t.data.to_string();

	return os;

}

#endif
