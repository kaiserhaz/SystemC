#ifndef MINIUART_H
#define MINIUART_H

#include "ClkUnit.h"
#include "TxUnit.h"
#include "RxUnit.h"

#include <iostream>

SC_MODULE (MiniUart){

	ClkUnit* ClkUnit_inst;
	TxUnit* TxUnit_inst;
	RxUnit* RxUnit_inst;

	sc_in<bool> sys_clk;
    sc_in<bool> reset;
    sc_in_resolved ce;
    sc_in_resolved rd;
	sc_in_resolved wr;
    sc_in< sc_lv<2> > addr;
    sc_in< sc_lv<8> > data_in;
	sc_out< sc_lv<8> > data_out;
    sc_out<bool> int_rx;
	sc_out<bool> int_tx;
    sc_out<bool> txd;
	sc_in<bool> rxd;

	sc_signal<bool> en_tx, en_rx, load, read, d_rdy, o_err, f_err, buf_empty, reg_empty;
    sc_signal< sc_uint<8> > tx_data, rx_data;
	sc_signal< sc_lv<8> > ctrl_status_reg;

	SC_CTOR( MiniUart ) : sys_clk("sys_clk"), reset("reset"), ce("ce"), rd("rd"), wr("wr"), addr("addr"), data_in("data_in"), data_out("data_out"), int_rx("int_rx"), 
		                  int_tx("int_tx"), txd("txd"), rxd("rxd")
	{

		ClkUnit_inst = new ClkUnit("ClkUnit0");
		TxUnit_inst = new TxUnit("TxUnit0");
		RxUnit_inst = new RxUnit("RxUnit0");

		ClkUnit_inst->sys_clk(sys_clk);
		ClkUnit_inst->reset(reset);
		ClkUnit_inst->enable_tx(en_tx);
		ClkUnit_inst->enable_rx(en_rx);

		TxUnit_inst->sys_clk(sys_clk);
		TxUnit_inst->reset(reset);
		TxUnit_inst->enable(en_tx);
		TxUnit_inst->load(load);	
		TxUnit_inst->data_in(tx_data);	
		TxUnit_inst->reg_empty(reg_empty);	
		TxUnit_inst->buf_empty(buf_empty);	
		TxUnit_inst->txd(txd);	

		RxUnit_inst->sys_clk(sys_clk);
		RxUnit_inst->reset(reset);
		RxUnit_inst->enable(en_rx);
		RxUnit_inst->read(read);	
		RxUnit_inst->data_out(rx_data);	
		RxUnit_inst->frame_err(f_err);	
		RxUnit_inst->output_err(o_err);	
		RxUnit_inst->data_rdy(d_rdy);
		RxUnit_inst->rxd(rxd);

		SC_METHOD( combinational );
			sensitive << d_rdy << o_err << f_err << buf_empty << reg_empty;
			dont_initialize();

		SC_THREAD( interface_process );

	}

	void interface_process() {

		sc_uint<8> temp_tx, temp_rx;

		while(true) {

			if(ce->read() == SC_LOGIC_0) {

				load.write(false);
				read.write(false);
				tx_data.write(0);
				data_out->write("ZZZZZZZZ");

			}

			else if(ce->read() == SC_LOGIC_1) {

				if(wr->read() == SC_LOGIC_0) {

					load.write(false);
					tx_data.write(0);

				}

				else if(wr->read() == SC_LOGIC_1) {

					if(addr->read() == "00") {

						load.write(true);
						temp_tx = (sc_uint<8>)data_in->read();  // Type conversion here
						tx_data.write(temp_tx);

					}

					else {

						load.write(false);
						tx_data.write(0);

					}
				}

				if(rd->read() == SC_LOGIC_0) {

					read.write(false);
					data_out->write("ZZZZZZZZ");

				}

				else if(rd->read() == SC_LOGIC_1) {

					if(addr->read() == "00") {

						read.write(true);
						temp_rx = (sc_lv<8>)rx_data.read();
						data_out->write(temp_rx);

					}

					else if(addr->read() == "01") {

						read.write(false);
						data_out->write(ctrl_status_reg.read());

					}

					else {

						read.write(false);
						data_out->write("ZZZZZZZZ");

					}

				}

			}

			wait(ce->default_event() | rd->default_event() | wr->default_event());

		}

	}

	void combinational() {

		sc_lv<8> temp_stat_reg;

		if(buf_empty.read() && !reg_empty.read()) {

			int_tx->write(true);

		}
		else {

			int_tx->write(false);

		}

		if(d_rdy.read()) {

			int_rx->write(true);

		}

		else {

			int_rx->write(false);

		}
		
		for(int i=7; i > 4; i--)
			temp_stat_reg[i] = SC_LOGIC_0;

		temp_stat_reg[4] = (sc_logic)reg_empty.read();
		temp_stat_reg[3] = (sc_logic)buf_empty.read();
		temp_stat_reg[2] = (sc_logic)d_rdy.read();
		temp_stat_reg[1] = (sc_logic)f_err.read();
		temp_stat_reg[0] = (sc_logic)o_err.read();

		ctrl_status_reg.write( temp_stat_reg );

		cout << " UART: Status register is : " << temp_stat_reg  << " @ " << sc_time_stamp() << endl;

		next_trigger(d_rdy.default_event() | o_err.default_event() | f_err.default_event() | buf_empty.default_event() | reg_empty.default_event());
	}

};

#endif
