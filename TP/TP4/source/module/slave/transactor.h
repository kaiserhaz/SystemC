#include "../../interface/slave/tlm_slave_bus_if.h"

/**
 * Event finder
 */

struct tlm_slave_if: public sc_port<tlm_slave_bus_if> {

	typedef tlm_slave_bus_if slave_if_t;

	sc_event_finder& rw_event() const {

		return *new sc_event_finder_t<slave_if_t> (*this, &slave_if_t::rw_event);
	
	}

};

/**
 * Transactor channel
 */

struct transactor : public sc_channel {
	
	// TLM Interface
	tlm_slave_if p_master;
	
	// RTL Clock Export Interface
	sc_export< sc_signal_out_if<bool> > sys_clk;
	
	// RTL Ports
	sc_in<bool> int_rx, int_tx;
	sc_in< sc_lv<8> > data_in;
	sc_out<bool> reset;
	sc_out<sc_logic> ce, rd, wr;
	sc_out< sc_lv<2> > addr;
	sc_out< sc_lv<8> > data_out;

	// Channel clock
	sc_clock trans_clk;

	// Channel members
	const sc_time CLK_PERIOD;
	sc_mutex bus_mutex;

	SC_HAS_PROCESS( transactor );

	transactor(sc_module_name name, unsigned clk_p): sc_channel(name), trans_clk("trans_clk", clk_p, SC_NS),
	                                                 ce(false), rd(false), wr(false), addr(0),
													 data_out("00000000"), CLK_PERIOD(clk_p, SC_NS)
	{

		SC_THREAD(transactor_thread);
			sensitive << p_master.rw_event();
		SC_METHOD(interrupt_0_method);
			sensitive << int_tx;
			dont_initialize();
		SC_METHOD(interrupt_1_method);
			sensitive << int_rx;
			dont_initialize();

		sys_clk.bind(trans_clk);

	}

	// Processes
	void transactor_thread();
	void interrupt_0_method();
	void interrupt_1_method();

	// Helper Functions
	void resetTest(void);
	void write(unsigned int addr, sc_uint<8> data);
	void read(unsigned int addr, sc_uint<8>& data);

};
