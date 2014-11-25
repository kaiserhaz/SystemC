#include <systemc.h>
#include "rtl_testbench.h"

// Processes

void RTL_TestBench::sysclk_method()
{
	sys_clk->write(clock.read());
}

void RTL_TestBench::boot_thread()
{
	cpt_car = 0;
	mess = "Hello !\n";

	resetTest();
	wait(CLK_PERIOD * 5);

	cout << "Write Boot " << mess[cpt_car] << endl;
	write(0x00, mess[cpt_car]);
	boot_done = true;
}

void RTL_TestBench::tx_interrupt_thread()
{
	while (true)
	{
		wait(int_tx->posedge_event());
		if(boot_done) {
			cout << "TX Interrupt at time : " << sc_time_stamp() << endl;
			if (cpt_car < sizeof(mess))
			{
				cpt_car += 1;
				cout << "Write " << mess[cpt_car] << endl;
				write(0x00, mess[cpt_car]);
			}
		}
	}
}

void RTL_TestBench::rx_interrupt_thread()
{
	sc_uint<8> value;
	while (true)
	{
		wait(int_rx->posedge_event());
		cout << "RX Interrupt at time : " << sc_time_stamp() << endl;
		read(0x00, value);
		cout << "Read " << char(value) << " @ " << sc_time_stamp() << endl;
	}
}

// Helper Functions

void RTL_TestBench::resetTest(void)
{
	bus_mutex.lock();
	addr->write(0);
	ce->write(SC_LOGIC_Z);
	wr->write(SC_LOGIC_Z);
	rd->write(SC_LOGIC_Z);
	data_out->write("ZZZZZZZZ");
	reset->write(true);
	wait(CLK_PERIOD * 20);
	reset->write(false);
	bus_mutex.unlock();
}

void RTL_TestBench::write(unsigned int addr_, sc_uint<8> data_)
{
	bus_mutex.lock();
	ce->write(SC_LOGIC_1);
	wr->write(SC_LOGIC_0);
	rd->write(SC_LOGIC_0);
	addr->write(addr_);
	data_out->write("00000000");
	wait(CLK_PERIOD);

	wr->write(SC_LOGIC_1);
	data_out->write(data_);
	
	wait(CLK_PERIOD * 3);

	wr->write(SC_LOGIC_0);
	wait(CLK_PERIOD);

	ce->write(SC_LOGIC_Z);
	wr->write(SC_LOGIC_Z);
	rd->write(SC_LOGIC_Z);
	data_out->write("ZZZZZZZZ");
	bus_mutex.unlock();
}

void RTL_TestBench::read(unsigned int addr_, sc_uint<8>& data_)
{
	bus_mutex.lock();
	ce->write(SC_LOGIC_1);
	wr->write(SC_LOGIC_0);
	rd->write(SC_LOGIC_0);
	addr->write(addr_);
	data_out->write("00000000");
	wait(CLK_PERIOD);

	rd->write(SC_LOGIC_1);
	wait(CLK_PERIOD * 3);

	data_ = data_in->read();

	rd->write(SC_LOGIC_0);
	wait(CLK_PERIOD);

	ce->write(SC_LOGIC_Z);
	wr->write(SC_LOGIC_Z);
	rd->write(SC_LOGIC_Z);
	data_out->write("ZZZZZZZZ");
	bus_mutex.unlock();
}