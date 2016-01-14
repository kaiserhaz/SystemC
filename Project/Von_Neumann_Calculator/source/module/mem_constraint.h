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

	scv_extensions<sc_logic> rst_n;                          // Verification extension for reset signal
	scv_extensions<sc_logic> r_nw;                           // Verification extension for read/write signal
	scv_extensions< a_word_t > addr;                         // Verification extension for address line
	scv_extensions< d_word_t > data;                         // Verification extension for data line

	/** Extension constructor **/

	SCV_EXTENSIONS_CTOR( mem_trans ) {

		SCV_FIELD(rst_n);                                    // Register reset as a field
		SCV_FIELD(r_nw);                                     // Register read/write as a field
		SCV_FIELD(addr);                                     // Register address line as a field
		SCV_FIELD(data);                                     // Register data line as a field

	}

};

/** Constraint class for mem_trans **/
class mem_constraint: public scv_constraint_base {

	public:

	scv_smart_ptr<mem_trans> m_t0;                           // Memory transaction instance

	/** SystemC verification constraint constructor **/

	SCV_CONSTRAINT_CTOR( mem_constraint ) {                  // Line 1125 of scv_constraint is throwing sc_logic to bool conversion warning

		SCV_CONSTRAINT( m_t0->addr() < MEM_SIZE );           // Constraint on address
		SCV_CONSTRAINT( m_t0->data() < 0x7E );               // Constraint on data, upper bound
		SCV_CONSTRAINT( m_t0->data() > 0x21 );               // Constraint on data, lower bound

	}

};

/** Constraint module to generate signal **/
SC_MODULE( mem_constr_module ) {

	/** Ports **/

	sc_out<sc_logic>               RST_N;                    // Reset, active low
	sc_out<sc_logic>               R_NW;                     // R/W signal; R active low
	sc_in<sc_logic>                OR_N;                     // Output ready, active low
	sc_in<sc_logic>                EOW_N;                    // End of write, active low
	sc_out< a_word_t >             ADDR;                     // Address line
	sc_inout_rv<MEM_DATA_WORD_LEN> DATA;                     // Data line
	

	/** Constraint class instance **/

	mem_constraint* mem_c0;

	/** Constraint module constructor **/

	SC_HAS_PROCESS( mem_constr_module );

	mem_constr_module(sc_module_name _name, unsigned int n_test) : sc_module(_name), _n_test(n_test)
    {

		SC_THREAD( mem_constr_module_thread );               // Register constraint module thread

		mem_c0 = new mem_constraint("mem_c0");               // Create new memory constraint class

	}

	/** Constraint module destructor **/

	~mem_constr_module() { delete mem_c0; }                  // Delete memory constraint class pointer

	/** Main thread **/

	void mem_constr_module_thread() {

		for(unsigned int ii=0; ii < _n_test; ii++) {         // Loop for as long as specified

			mem_c0->m_t0->next();                            // Randomize transaction

			cout << sc_time_stamp() << " CONSTR_MOD: Transaction value:\n" << to_string() << endl;
			//cout << sc_time_stamp() << " CONSTR_MOD: Reset value: " << mem_c0->m_t0->rst_n.read() << endl;

			if(mem_c0->m_t0->r_nw.read() == SC_LOGIC_1) {    // Write case

				write();                                     // Write data on line

				wait(EOW_N->negedge_event());                // Wait for write to finish

				cout << sc_time_stamp() << " CONSTR_MOD: Value write " << endl;

			}

			else {

				write();                                     // Write data on line

				wait(OR_N->negedge_event());                 // Wait for output to be ready

				cout << sc_time_stamp() << " CONSTR_MOD: Value read: " << DATA->read() << endl;

			}

		}

		sc_stop();                                           // Stop simulation after end of loop
		
	}

	/** Functions **/

	// Disable randomization of reset
	void disable_rst_randomization(bool dis, sc_logic state) {

		if(dis)
			mem_c0->m_t0->rst_n.disable_randomization();     // Disable random resets
		else
			mem_c0->m_t0->rst_n.enable_randomization();      // Enable random resets

		mem_c0->m_t0->rst_n.write(state);                    // Write final reset state

	}

	private:

	/** Variables **/

	unsigned int _n_test;                                    // Number of test run

	/** SystemC phase callbacks **/

	void end_of_elaboration() {

		ADDR->write(a_word_t('0'));                          // Initialize address line
		DATA->write(d_word_t('z'));                          // Initialize data line
		//R_NW->write(SC_LOGIC_Z);                             // Initialize read/write

	}

	/** Functions **/

    // Write on the bus according to a specific protocol
	void write() {

		RST_N->write(mem_c0->m_t0->rst_n.read());            // Write reset
		ADDR->write(mem_c0->m_t0->addr.read());              // Write address
		
        R_NW->write(SC_LOGIC_Z);                             // Write read/write line at high impedance
		
		cout << sc_time_stamp() << " CONSTR_MOD: Read/write Z " << endl;

		DATA->write(d_word_t(0));                            // Set line to 0

		wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT);           // Setup wait before writing
		
		R_NW->write(mem_c0->m_t0->r_nw.read());              // Write read/write

		cout << sc_time_stamp() << " CONSTR_MOD: Read/write asserted " << endl;

		DATA->write(mem_c0->m_t0->data.read());              // Write data

		wait(MEM_HOLD_WRITE_TIME, MEM_TIME_UNIT);            // Hold wait

		R_NW->write(SC_LOGIC_Z);                             // Write read/write line at high impedance

		cout << sc_time_stamp() << " CONSTR_MOD: Read/write Z " << endl;

		DATA->write(d_word_t(0));                            // Set line to 0

		wait(MEM_SETUP_WRITE_TIME, MEM_TIME_UNIT);           // Post-hold wait

	    DATA->write(d_word_t('z'));                          // Return line to high impedance

	}

	// Randomize transaction
	void next() {

		mem_c0->m_t0->next();                                // Runs the smart pointer next

	}

	// Converts the mem_trans object to string
	mem_trans to_string() {

		return *mem_c0->m_t0->get_instance();                // Dummy to_string function,
		                                                     //  actually returns the mem_trans instrance

	}	

};

#endif
