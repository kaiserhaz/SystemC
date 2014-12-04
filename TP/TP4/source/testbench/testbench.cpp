#include "testbench.h"

/**
 * Testbench module implementation
 */

testbench::testbench(sc_module_name name) {

	p_inst = new processor("p_inst");
	t_inst = new transactor("t_inst", 25);
	tlm_bus_inst = new tlm_bus();
	m_inst = new MiniUart("m_inst");

	p_inst->p_slave(*tlm_bus_inst);
	t_inst->p_master(*tlm_bus_inst);

	t_inst->int_tx(int_tx);
	t_inst->int_rx(int_rx);
	t_inst->reset(reset);
	t_inst->ce(ce);
	t_inst->rd(rd);
	t_inst->wr(wr);
	t_inst->addr(addr);
	t_inst->data_in(data_in);
	t_inst->data_out(data_out);
	
	m_inst->sys_clk(t_inst->sys_clk);
	m_inst->int_tx(int_tx);
	m_inst->int_rx(int_rx);
	m_inst->reset(reset);
	m_inst->ce(ce);
	m_inst->rd(rd);
	m_inst->wr(wr);
	m_inst->addr(addr);
	m_inst->data_in(data_out);
	m_inst->data_out(data_in);
	m_inst->txd(txd_rxd);
	m_inst->rxd(txd_rxd);

	tf = sc_create_vcd_trace_file("trans_trace");
	sc_write_comment(tf, "Simulation of Transactor");
	tf->set_time_unit(1, SC_NS);

	t_inst->sys_clk.trace(tf);

	sc_trace(tf, reset, "reset");
	sc_trace(tf, int_rx, "int_rx");
	sc_trace(tf, int_tx, "int_tx");
	sc_trace(tf, txd_rxd, "txd_rxd");
	sc_trace(tf, ce, "ce");
	sc_trace(tf, rd, "rd");
	sc_trace(tf, wr, "wr");
	sc_trace(tf, addr, "addr");
	sc_trace(tf, data_in, "data_in");
	sc_trace(tf, data_out, "data_out");
	
	sc_trace(tf, t_inst->p_master->getAddress(), "addr");
	sc_trace(tf, t_inst->p_master->getData(), "data");
	sc_trace(tf, t_inst->p_master->is_read(), "rw");

}
