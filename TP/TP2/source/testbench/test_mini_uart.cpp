#include <systemc.h>
#include "../modules/ClkUnit.h"
#include "../modules/TxUnit.h"
#include "../modules/RxUnit.h"
#include "../modules/MiniUart.h"
#include "RTL_testbench.h"

void test_miniuart()
{
	sc_set_time_resolution(1, SC_NS);

	sc_signal<bool> sys_clk, reset, int_rx, int_tx, txd_rxd;
	sc_signal_resolved ce, rd, wr;
	sc_signal_rv<2> addr;
	sc_signal_rv<8> data_in;
	sc_signal_rv<8> data_out;

	MiniUart MiniUart_inst("MiniUart");
		MiniUart_inst.sys_clk(sys_clk);
		MiniUart_inst.reset(reset);
		MiniUart_inst.ce(ce);
		MiniUart_inst.rd(rd);	
		MiniUart_inst.wr(wr);	
		MiniUart_inst.addr(addr);	
		MiniUart_inst.data_in(data_in);	
		MiniUart_inst.data_out(data_out);	

		MiniUart_inst.int_rx(int_rx);	
		MiniUart_inst.int_tx(int_tx);

		MiniUart_inst.rxd(txd_rxd);	
		MiniUart_inst.txd(txd_rxd);	

	RTL_TestBench RTL_TestBench_inst("RTL_TestBench");
		RTL_TestBench_inst.sys_clk(sys_clk);
		RTL_TestBench_inst.reset(reset);
		RTL_TestBench_inst.ce(ce);
		RTL_TestBench_inst.rd(rd);	
		RTL_TestBench_inst.wr(wr);	
		RTL_TestBench_inst.addr(addr);	
		RTL_TestBench_inst.data_in(data_out);	
		RTL_TestBench_inst.data_out(data_in);	

		RTL_TestBench_inst.int_rx(int_rx);	
		RTL_TestBench_inst.int_tx(int_tx);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_miniuart");
	sc_write_comment(tf, "Simulation of Mini Uart");
	((vcd_trace_file*)tf)->set_time_unit(1,SC_NS);	// 10exp(-9) = 1 ns

	sc_trace(tf,sys_clk, "sys_clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,ce,"ce");
	sc_trace(tf,rd,"rd");
	sc_trace(tf,wr,"wr");
	sc_trace(tf,addr,"addr");
	sc_trace(tf,data_in,"data_in");
	sc_trace(tf,data_out,"data_out");
	sc_trace(tf,int_rx,"int_rx");
	sc_trace(tf,int_tx,"int_tx");
	sc_trace(tf,txd_rxd,"txd_rxd");

	sc_start(8, SC_MS);

	sc_close_vcd_trace_file(tf);
}
