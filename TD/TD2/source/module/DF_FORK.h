#ifndef DF_FORK_H
#define DF_FORK_H

#include <iostream>
#include <systemc.h>

SC_MODULE( DF_FORK ) {

	sc_fifo_in<double> df_f_added_value;
	sc_fifo_out<double> df_f_feedback;
	sc_fifo_out<double> df_f_result;

	SC_CTOR( DF_FORK ) : df_f_added_value("added_value"), df_f_feedback("feedback"), df_f_result("result")
	{
		SC_THREAD( df_f_thread );
	}

	void df_f_thread(void) {
		
		double temp_value = 0.0;

		//cout << sc_time_stamp() << " DF_F : Init " << endl;
		
		df_f_feedback->write(0.0);

		while(true) {
			
			//cout << sc_time_stamp() << " DF_F : Entered loop " << endl;

			temp_value = df_f_added_value->read();

			//cout << sc_time_stamp() << " DF_F : Value read " << endl;

			wait(10, SC_NS);
			
			df_f_feedback->write(temp_value);
			df_f_result->write(temp_value);

			//cout << sc_time_stamp() << " DF_F : Values written " << endl;
						
		}
		
	}
	
};

#endif