#ifndef DF_CONSTANT_H
#define DF_CONSTANT_H

#include <iostream>
#include <systemc.h>

SC_MODULE( DF_CONSTANT ) {

	sc_fifo_out<double> df_c_const_value;
	
	double const_value;
	
	SC_HAS_PROCESS( DF_CONSTANT );
	
	DF_CONSTANT(sc_module_name module_name, double N) : sc_module(module_name), df_c_const_value("const_value"), const_value(N)
	{
		SC_THREAD( df_c_thread );
	}

	void df_c_thread(void) {

		//cout << " DF_C : Init " << endl;
	
		while(true) {
			
			//cout << " DF_C : Entered loop " << endl;

			wait(1, SC_MS);

			df_c_const_value->write(const_value);
			
			//cout << " DF_C : Constant written " << endl;
			
		}
	
	}
	
};

#endif