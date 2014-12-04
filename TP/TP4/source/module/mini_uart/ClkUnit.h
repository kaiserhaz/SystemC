#ifndef CLKUNIT_H
#define CLKUNIT_H

#include <iostream>
#include <systemc.h>

SC_MODULE (ClkUnit){

	sc_in<bool> sys_clk;
    sc_in<bool> reset;
    sc_out<bool> enable_tx;
    sc_out<bool> enable_rx;

	SC_CTOR(ClkUnit) : sys_clk("sys_clk"), \
					   reset("reset"), \
					   enable_tx("enable_tx"), \
					   enable_rx("enable_rx")
	{

		SC_THREAD(clkUnit_thread);

	}

	void clkUnit_thread(){

		int compteurclk=0, compteurrx=0;

		while(1){

			wait(sys_clk->posedge_event());

			if (reset->read()) {

				compteurclk=0;
				compteurrx=0;
				enable_tx->write(false);
				enable_rx->write(false);

			}

			else {

				if (compteurclk == 4167) {

					compteurclk = 1;
					enable_tx->write(true);

				}

				else
				{

					enable_tx->write(false);
					compteurclk++;

				}

				if (compteurrx == 261) {

					compteurrx = 1;
					enable_rx->write(true);

				}

				else
				{

					enable_rx->write(false);
					compteurrx++;

				}

			}

		}

	}

};

#endif
