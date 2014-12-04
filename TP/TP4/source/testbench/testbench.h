#include "../module/master/processor.h"
#include "../module/slave/transactor.h"
#include "../bus/tlm_bus.h"
#include "../module/mini_uart/MiniUart.h"

/**
 * Testbench module
 */

SC_MODULE( testbench ) {

	processor* p_inst;
	transactor* t_inst;
	tlm_bus* tlm_bus_inst;
	MiniUart* m_inst;

	sc_signal<bool> reset, int_rx, int_tx, txd_rxd;
    sc_signal_resolved ce, rd, wr;
    sc_signal< sc_lv<2> > addr;
    sc_signal< sc_lv<8> > data_in, data_out;

	sc_trace_file* tf;

	SC_HAS_PROCESS( testbench );

	testbench(sc_module_name name);

};
