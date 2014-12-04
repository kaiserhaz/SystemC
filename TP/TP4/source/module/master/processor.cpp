#include "processor.h"

/**
 * Processor module implementation
 */

void processor::boot_thread()
{

	cpt_car = 0;
	mess = "Hello !\n";

	cout << " PROCESSOR: Requesting boot " << endl;

	p_slave->write2slave(0xFF, 1);

	cout << " PROCESSOR: Boot complete " << endl;

	cout << " PROCESSOR: Write Boot " << mess[cpt_car] << endl;
	p_slave->write2slave(0x00, mess[cpt_car]);
	boot_done = true;

}

void processor::tx_interrupt_thread()
{

	while (true) {

		wait(p_slave->int0_event());

		if(boot_done) {

			cout << " PROCESSOR: TX Interrupt at time : " << sc_time_stamp() << endl;

			if (cpt_car < sizeof(mess)) {

				cpt_car += 1;
				cout << " PROCESSOR: Write " << mess[cpt_car] << endl;

				p_slave->write2slave(0x00, mess[cpt_car]);

			}

		}

	}

}

void processor::rx_interrupt_thread()
{

	sc_uint<8> value;

	while (true) {

		wait(p_slave->int1_event());

		cout << " PROCESSOR: RX Interrupt at time : " << sc_time_stamp() << endl;

		value = (sc_uint<8>)p_slave->read2slave(0x00);

		cout << " PROCESSOR: Read " << char(value) << " @ " << sc_time_stamp() << endl;

	}

}
