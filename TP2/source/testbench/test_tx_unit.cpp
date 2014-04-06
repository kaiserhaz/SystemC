#include <systemc.h>
#include "../modules/ClkUnit.h"
#include "../modules/TxUnit.h"

void test_tx_unit()
{
	sc_set_time_resolution(1, SC_NS);

	sc_signal<bool> reset, enable_tx, enable_rx, load, reg_empty, buf_empty, txd;
	sc_signal<sc_uint<8> > tx_data;
	sc_clock clk("clk",25,SC_NS);	// 40MHz
	
	ClkUnit ClkUnit_inst("ClkUnit");
		ClkUnit_inst.sys_clk(clk);
		ClkUnit_inst.reset(reset);
		ClkUnit_inst.enable_tx(enable_tx);
		ClkUnit_inst.enable_rx(enable_rx);

	TxUnit TxUnit_inst("TxUnit");
		TxUnit_inst.sys_clk(clk);
		TxUnit_inst.reset(reset);
		TxUnit_inst.enable(enable_tx);
		TxUnit_inst.load(load);	
		TxUnit_inst.data_in(tx_data);	
		TxUnit_inst.reg_empty(reg_empty);	
		TxUnit_inst.buf_empty(buf_empty);	
		TxUnit_inst.txd(txd);	

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_txunit");
	sc_write_comment(tf, "Simulation of Tx Unit");
	((vcd_trace_file*)tf)->set_time_unit(1, SC_NS);	// 10exp(-9) = 1 ns

	sc_trace(tf,clk, "clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,enable_tx,"enable_tx");
	sc_trace(tf,load,"load");
	sc_trace(tf,tx_data,"tx_data");
	sc_trace(tf,reg_empty,"reg_empty");
	sc_trace(tf,buf_empty,"buf_empty");
	sc_trace(tf,txd,"txd");

	// Reset
	cout << "Reset ..." << endl;
	load.write(false);
	reset.write(true);
	sc_start(1, SC_US);
	reset.write(false);
	sc_start(1, SC_US);

	// Load
	cout << "Load ..." << endl;
	tx_data.write(0x0D);
	load.write(true);
	sc_start(10, SC_US);

	// Send
	cout << "Send on TxD ..." << endl;
	load.write(false);
	sc_start(2, SC_MS);

	sc_close_vcd_trace_file(tf);
}
