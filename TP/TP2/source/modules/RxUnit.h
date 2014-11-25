#ifndef RXUNIT_H
#define RXUNIT_H

#include <systemc.h>

SC_MODULE( RxUnit ) {

	sc_in<bool> sys_clk;
	sc_in<bool> reset;

	sc_in<bool> enable;
	sc_in<bool> read;
	sc_in<bool> rxd;

	sc_out< sc_uint<8> > data_out;
	sc_out<bool> frame_err;
	sc_out<bool> output_err;
	sc_out<bool> data_rdy;

	SC_CTOR( RxUnit ) : sys_clk("sys_clk"), \
						reset("reset"), \
						enable("enable"), \
						read("read"), \
						rxd("rxd"), \
		                data_out("data_out"), \
						frame_err("frame_err"), \
						output_err("output_err"), \
						data_rdy("data_rdy")
	{

		SC_THREAD( rx_unit_thread );
	
	}

	void rx_unit_thread(void) {

		bool front_detected;
		bool synchronised;
		bool temp, old_val, new_val, shift_register[8];

		int i, delay_counter, op_counter;

		sc_uint<8> temp_data_out;

		front_detected = false;
		synchronised = false;

		old_val = rxd->read();
		new_val = rxd->read();

		delay_counter = 0;
		op_counter = 0;

		for(i=0; i<8; i++) {

			shift_register[i] = false;

		}

		while( true ) {

			if( reset->read() == true ) {

				data_out->write(0);
				frame_err->write(false);
				output_err->write(false);
				data_rdy->write(false);

				op_counter = 0;
				temp_data_out = 0;
				front_detected = false;
				synchronised = false;
				delay_counter = 0;
				new_val = rxd->read();
				old_val = rxd->read();

			}

			else {

				if( enable->read() == true ) {

					// Find front
					//  If detected, then slow down the clock by using a counter
					//  Else continue sampling until detected
					if( front_detected == false ) {

						new_val = rxd->read();

						if( old_val != new_val ) {

							front_detected = true;

						}

						else {

							old_val = new_val;

						}
					}

					// Sample
					//  Validate synchronised condition by waiting 7 cycles
					//  Then wait 16 cycles, then read from rxd
					else {

						if( synchronised == false ) {

							delay_counter += 1;

							if( delay_counter >= 7 ) {

								synchronised = true;
								delay_counter = 0;

							}

						}

						else {

							delay_counter += 1;

							if( delay_counter >= 16 ) {

								temp = rxd->read();
								delay_counter = 0;

								if( (op_counter >= 0) && (op_counter < 8) ) {

									// Shift
									//  Shift bits from N-1 to N
									//  Store temp variable in 0
									//  Shift_register is treated as 7..0
									for(i = 0; i < 7; i++)
										shift_register[7-i] = shift_register[7-i-1];
									
									shift_register[0] = temp;

								}

								op_counter += 1;

							}

						}

					}

					// Drive
					//  Drive signals after 10 read cycles
					if( op_counter >= 9 ) {

						if( data_rdy->read() == true ) {

							output_err->write(true);

						}

						else {

							output_err->write(false);

						}
						
						data_rdy->write(true);
						
						if( temp == false ) {

							frame_err->write(true);

						}

						else {

							frame_err->write(false);

						}

						for(i = 0; i < 8; i++)
							temp_data_out[i] = shift_register[i];

						data_out->write(temp_data_out);

						op_counter = 0;
						front_detected = false;
						synchronised = false;
						delay_counter = 0;
						new_val = rxd->read();
						old_val = rxd->read();

					}
				}

				if( read->read() == true ) {

					if( data_rdy->read() == true ) {

						data_rdy->write(false);

					}
				}
			}
			
			wait( sys_clk->posedge_event() );

		}

	}

};

#endif