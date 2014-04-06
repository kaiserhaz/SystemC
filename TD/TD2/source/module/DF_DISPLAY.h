#ifndef DF_DISPLAY_H
#define DF_DISPLAY_H

#include <iostream>
#include <systemc.h>

SC_MODULE( DF_DISPLAY ) {

	sc_fifo_in<double> df_d_result;
	
	int nn;
	
	SC_HAS_PROCESS( DF_DISPLAY );
	
	DF_DISPLAY(sc_module_name module_name, int N) : sc_module(module_name), df_d_result("result"), nn(N)
	{
		SC_THREAD( df_d_thread );
	}

	void df_d_thread(void) {
	
		double out = 0.0;
		int i;

		//cout << sc_time_stamp() << " DF_D : Init " << endl;
	
		while(true) {

			//cout << sc_time_stamp() << " DF_D : Entered loop " << endl;
		
			for(i = 0; i < nn; i++) {
				
				//cout << sc_time_stamp() << " DF_D : Entered for loop " << endl;
				
				out = df_d_result->read();
				
				cout << " DF_D : Simulation time : " << sc_time_stamp() << ". Value : " << out << endl;

				//wait(1, SC_NS);
			
			}
		}
	
	}
	
};

#endif