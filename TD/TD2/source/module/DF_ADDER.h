#ifndef DF_ADDER_H
#define DF_ADDER_H

#include <iostream>
#include <systemc.h>

SC_MODULE( DF_ADDER ) {

	sc_fifo_in<double> df_a_feedback;
	sc_fifo_in<double> df_a_const_value;
	sc_fifo_out<double> df_a_added_value;
	
	SC_CTOR( DF_ADDER ) : df_a_feedback("feedback"), df_a_const_value("const_value"), df_a_added_value("added_value")
	{
		SC_THREAD( df_a_thread );
	}

	void df_a_thread(void) {
		
		double temp_value = 0.0;

		//cout << sc_time_stamp() << " DF_A : Init " << endl;
		
		while(true) {
		
			//cout << sc_time_stamp() << " DF_A : Entered loop " << endl;

			temp_value = df_a_const_value->read();

			//cout << sc_time_stamp() << " DF_A : Value read " << endl;

			temp_value =  temp_value + df_a_feedback->read();

			//cout << sc_time_stamp() << " DF_A : Value read definite " << endl;

			wait(100, SC_NS);
			
			df_a_added_value->write(temp_value);

			//cout << sc_time_stamp() << " DF_A : Value written " << endl;
					
		}
		
	}
	
};

#endif