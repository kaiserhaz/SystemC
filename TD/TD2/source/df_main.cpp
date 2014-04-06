#include "module/DF_CONSTANT.h"
#include "module/DF_ADDER.h"
#include "module/DF_FORK.h"
#include "module/DF_DISPLAY.h"
#include <systemc.h>

int sc_main(int argc, char* argv[]) {
	sc_fifo<double> const_value(100), feedback(100), added_value(100), result(100);

	cout << " FIFOs declared " << endl;

	DF_CONSTANT DF_C0_inst("DF_Constant0", 2.17);
		DF_C0_inst.df_c_const_value(const_value);
	
	cout << " Constant instance setup complete " << endl;

	DF_ADDER DF_A0_inst("DF_Adder0");
		DF_A0_inst.df_a_feedback(feedback);
		DF_A0_inst.df_a_const_value(const_value);
		DF_A0_inst.df_a_added_value(added_value);

	cout << " Adder setup complete " << endl;
	
	DF_FORK DF_F0_inst("DF_Fork0");
		DF_F0_inst.df_f_added_value(added_value);
		DF_F0_inst.df_f_feedback(feedback);
		DF_F0_inst.df_f_result(result);
		
	cout << " Fork setup complete " << endl;
		
	DF_DISPLAY DF_D0_inst("DF_Display0", 15);
		DF_D0_inst.df_d_result(result);
		
	cout << " Display setup complete " << endl;

	cout << " Start simulation " << endl;

	sc_start(50, SC_MS);

	system("pause");

	return 0;
}