#include <systemc.h>
#include "../modules/ClkUnit.h"
#include "../modules/TxUnit.h"
#include "../modules/RxUnit.h"

void test_rx_unit()
{
	sc_set_time_resolution(1, SC_NS);

	sc_signal<bool> reset, enable_tx, load, reg_empty, buf_empty;
	sc_signal<bool> enable_rx, read, txd_rxd, d_rdy, o_err, f_err;
	sc_signal<sc_uint<8> > tx_data, rx_data;
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
		TxUnit_inst.txd(txd_rxd);	

	RxUnit RxUnit_inst("RxUnit");
		RxUnit_inst.sys_clk(clk);
		RxUnit_inst.reset(reset);
		RxUnit_inst.enable(enable_rx);
		RxUnit_inst.read(read);	
		RxUnit_inst.data_out(rx_data);	
		RxUnit_inst.frame_err(f_err);	
		RxUnit_inst.output_err(o_err);	
		RxUnit_inst.data_rdy(d_rdy);
		RxUnit_inst.rxd(txd_rxd);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_rxunit");
	sc_write_comment(tf, "Simulation of Tx Unit");
	((vcd_trace_file*)tf)->set_time_unit(1, SC_NS);	// 10exp(-9) = 1 ns

	sc_trace(tf,clk, "clk");
	sc_trace(tf,reset,"reset");

	sc_trace(tf,load,"load");
	sc_trace(tf,tx_data,"tx_data");
	sc_trace(tf,buf_empty,"buf_empty");
	sc_trace(tf,reg_empty,"reg_empty");

	sc_trace(tf,txd_rxd,"txd_rxd");

	sc_trace(tf,enable_rx,"enable_rx");
	sc_trace(tf,read,"read");
	sc_trace(tf,rx_data,"rx_data");
	sc_trace(tf,f_err,"f_err");
	sc_trace(tf,o_err,"o_err");
	sc_trace(tf,d_rdy,"d_rdy");

	// Reset
	cout << "Reset ..." << endl;
	load.write(false);
	reset.write(true);
	sc_start(1, SC_US);
	reset.write(false);
	sc_start(1, SC_US);

	// Load
	cout << "Load ..." << endl;
	tx_data.write(0x4c);
	load.write(true);
	sc_start(10, SC_US);

	// First Send
	cout << "Send on TxD ..." << endl;
	load.write(false);
	sc_start(1.5, SC_MS);

	// First Read
	cout << "Read on RxD ..." << endl;
	read.write(true);
	sc_start(5, SC_US);
	read.write(false);
	sc_start(1, SC_US);

	// Load
	cout << "Load ..." << endl;
	tx_data.write(0x6f);
	load.write(true);
	sc_start(10, SC_US);

	// Second Send
	cout << "Send on TxD ..." << endl;
	load.write(false);
	sc_start(1.5, SC_MS);

	// Second Read
	cout << "Read on RxD ..." << endl;
	read.write(true);
	sc_start(5, SC_US);
	read.write(false);
	sc_start(1, SC_US);

	// Load
	cout << "Load ..." << endl;
	tx_data.write(0x4c);
	load.write(true);
	sc_start(10, SC_US);

	// Third Send
	cout << "Send on TxD ..." << endl;
	load.write(false);
	sc_start(1.5, SC_MS);

	// Load
	cout << "Load ..." << endl;
	tx_data.write(0x0d);
	load.write(true);
	sc_start(10, SC_US);

	// Fourth Send
	cout << "Send on TxD ..." << endl;
	load.write(false);
	sc_start(1.5, SC_MS);

	sc_close_vcd_trace_file(tf);
}