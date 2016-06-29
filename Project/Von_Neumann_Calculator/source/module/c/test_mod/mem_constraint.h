/**
 * Constrained random memory tester module
 */

/** Include guard **/
#ifndef MEM_CONSTRAINT_H
#define MEM_CONSTRAINT_H

/** Includes **/
#include <systemc.h>
#include <scv.h>
#include "..\vnc_inc.h"

/** SCV Extension for mem_trans type **/
template<> class scv_extensions<mem_trans>: public scv_extensions_base<mem_trans> {

	public:

	/** Extension fields **/

	scv_extensions<bool> rst_n;               // Verification extension for reset signal
	scv_extensions<bool> r_nw;                // Verification extension for read/write signal
	scv_extensions< a_word_t > addr;          // Verification extension for address line
	scv_extensions< d_word_t > data;          // Verification extension for data line

	/** Extension constructor **/

	SCV_EXTENSIONS_CTOR( mem_trans ) {

		SCV_FIELD(rst_n);                     // Register reset as a field
		SCV_FIELD(r_nw);                      // Register read/write as a field
		SCV_FIELD(addr);                      // Register address line as a field
		SCV_FIELD(data);                      // Register data line as a field

	}

};

/** Constraint class for mem_trans **/
class mem_constraint: public scv_constraint_base {

	public:

	scv_smart_ptr<mem_trans> m_t0;            // Memory transaction instance

	/** SystemC verification constraint constructor **/

	SCV_CONSTRAINT_CTOR( mem_constraint ) {

//		SCV_CONSTRAINT( m_t0->addr() < MEM_SIZE ); // Constraint on address
		SCV_CONSTRAINT( m_t0->data() < 0x7E ); // Constraint on data, upper bound
		SCV_CONSTRAINT( m_t0->data() > 0x21 ); // Constraint on data, lower bound

	}

};

/** Constraint module to generate signal **/
SC_MODULE( mem_constr_module ) {

	/** Ports **/
	sc_in<bool>                    CLK;       // Clock input
	sc_out<bool>                   RST_N;     // Reset input
	sc_out<bool>                   R_NW;      // Read/write input
	sc_out< a_word_t >             ADDR;      // Address line input
	sc_in< d_word_t >              DATAIN;    // Data in line
	sc_out< d_word_t >             DATAOUT;   // Data out line
	
	/** Constraint class instance **/

	mem_constraint* mem_c0;

	/** Constraint module constructor **/

	SC_HAS_PROCESS( mem_constr_module );

	mem_constr_module(sc_module_name _name, unsigned int n_test) : sc_module(_name), _n_test(n_test)
    {

		SC_THREAD( mem_constr_module_thread ); // Register constraint module thread

		mem_c0 = new mem_constraint("mem_c0"); // Create new memory constraint class

	}

	/** Constraint module destructor **/

	~mem_constr_module() { delete mem_c0; }   // Delete memory constraint class pointer

	/** Functions **/

	// Disable randomization of reset
	void disable_rst_randomization(bool dis, bool state) {

		if(dis)
			mem_c0->m_t0->rst_n.disable_randomization(); // Disable random resets
		else
			mem_c0->m_t0->rst_n.enable_randomization();  // Enable random resets

		mem_c0->m_t0->rst_n.write(state);     // Write final reset state

	}

	// Randomize transaction
	void next() {

		mem_c0->m_t0->next();                 // Runs the smart pointer next

	}

	private:

	/** Main thread **/

	void mem_constr_module_thread() {

		for(unsigned int ii=0; ii < _n_test; ii++) { // Loop for as long as specified

			mem_c0->m_t0->next();             // Randomize transaction

			RST_N->write(mem_c0->m_t0->rst_n);

			cout << sc_time_stamp() << " CONSTR_MOD: Transaction value:\n" << to_string() << endl;

			if(mem_c0->m_t0->r_nw.read() == SC_LOGIC_1) { // Write case

				wait(CLK->posedge_event());   // Wait for clock

				mem_constr_write();           // Write data on line

				cout << sc_time_stamp() << " CONSTR_MOD: Value write \n" << endl;

			}

			else {

				mem_constr_read();            // Write data on line

				cout << sc_time_stamp() << " CONSTR_MOD: Value read: " << _data << "\n" << endl;

			}

		}
		
	}

	/** Variables **/

	unsigned int _n_test;                     // Number of test run
	signed short _data;                       // Data variable

    // Execute a write command according to a specific protocol
	void mem_constr_write() {

		ADDR->write(mem_c0->m_t0->addr.read()); // Write address
		DATAOUT->write(mem_c0->m_t0->data.read()); // Write data
		R_NW->write(mem_c0->m_t0->r_nw.read()); // Write read/write

		wait(SC_ZERO_TIME);

	}

	// Read according to a specific protocol
	void mem_constr_read() {

		ADDR->write(mem_c0->m_t0->addr.read()); // Write address
		R_NW->write(mem_c0->m_t0->r_nw.read()); // Write read/write

		wait(SC_ZERO_TIME);

		_data = DATAIN->read().to_int();        // Read data

		wait(SC_ZERO_TIME);

	}

	// Converts the mem_trans object to string
	mem_trans to_string() {

		return *mem_c0->m_t0->get_instance(); // Dummy to_string function,
		                                      //  actually returns the mem_trans instrance

	}	

};

#endif
