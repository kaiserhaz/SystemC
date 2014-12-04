#ifndef TX_UNIT_H
#define TX_UNIT_H

#include <iostream>
#include <systemc.h>

SC_MODULE (TxUnit){

	sc_in<bool> reset, enable, load;
	sc_in< sc_uint<8> > data_in;
	sc_out<bool> reg_empty, buf_empty, txd;
	sc_in<bool> sys_clk;

	sc_signal<bool> buffer[8];
	sc_signal<bool> reg[8];
	bool ss, ld;
	int j;

	sc_uint<8> tmp_d_in;

	SC_CTOR(TxUnit): sys_clk("sys_clk"), \
					 reset("reset"), \
					 enable("enable"), \
					 load("load"), \
					 data_in("data_in"), \
					 reg_empty("reg_empty"), \
					 buf_empty("buf_empty"), \
					 txd("txd")
	{

		SC_THREAD(tx_unit_thread);

	}

	void tx_unit_thread() {

		while(true) {

			if(reset->read() == true) {

				txd->write(true);

				buf_empty->write(true);
				ss = false;
				ld = false;

				reg_empty->write(true);

				j = 0;

			}

			else {

				if(load->read() == true) {

					buf_empty->write(false);
					tmp_d_in = data_in->read();

					for(int i=0; i<8; i++)
						buffer[i] = (tmp_d_in >> (7-i)) & 1;

					ld = true;

				}

				else {

					if ( ss == false && ld == true) {

						buf_empty->write(true);

						for(int i=0; i<8; i++)
							reg[i] = buffer[i];

						ss = true;

						ld = false;

					}

				}

				if (enable->read() == true) {

					if(ss == true) {

						if(j == 0) {

							txd->write(false);
							reg_empty->write(false);

							j++;

						}

						else if((j>0) && (j<9)) {

							txd->write(reg[j-1]);

							j++;

						}

						else if(j>=9) {

							txd->write(true);

							reg_empty->write(true);

							ss = false;

							j = 0;

						}

					}

				}

			}

			wait(sys_clk.posedge_event());

		}

	}

};

#endif
