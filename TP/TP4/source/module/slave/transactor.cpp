#include "transactor.h"

/**
 * Transactor channel implementation
 */

void transactor::transactor_thread(void) {

	sc_uint<8> tmp;

	while(1) {

		wait(p_master->rw_event());

		cout << " TRANSACTOR: RW event triggered " << endl;

		if(p_master->is_read()) {

			read(p_master->getAddress(), tmp);

			p_master->senddata2master((int)tmp);

			cout << " TRANSACTOR: Sending to processor: " << tmp << endl;

		}
		else {

			if(p_master->getAddress() == 0xFF) {

				resetTest();

				cout << " TRANSACTOR: Resetting lines " << endl;

			}
			else {

				write(p_master->getAddress(), (sc_uint<8>)p_master->getData());

				cout << " TRANSACTOR: Writing to UART: " << p_master->getData() << " @ " << p_master->getAddress() << endl;

			}

		}
			
		p_master->w2slave_ack();

	}

}

void transactor::interrupt_0_method(void) {

	p_master->int0_notify();

}

void transactor::interrupt_1_method(void) {

	p_master->int1_notify();

}

/**
 * Helper functions
 */

void transactor::resetTest(void)
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

void transactor::write(unsigned int addr_, sc_uint<8> data_)
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

void transactor::read(unsigned int addr_, sc_uint<8>& data_)
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
