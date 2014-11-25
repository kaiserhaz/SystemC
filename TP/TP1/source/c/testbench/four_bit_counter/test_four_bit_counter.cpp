#include <iostream>
#include <systemc.h>
#include "test_four_bit_counter.h"

SC_MODULE_EXPORT(test_four_bit_counter);

void test_four_bit_counter::clock_assign(void) {
		
	if(sys_clk0.posedge()) {
	
		t_clk.write(SC_LOGIC_1);
		
		#ifdef MEMORY_RTL_H
		
		t_clk2.write(true);
		
		#endif
		
	}
	else {
	
		t_clk.write(SC_LOGIC_0);
		
		#ifdef MEMORY_RTL_H
		
		t_clk2.write(false);
		
		#endif
		
	}
	
	next_trigger(sys_clk0.default_event());
	
}

void test_four_bit_counter::test_bench(void) {
	
	cout << " Resetting " << endl;
	
	t_rst.write(SC_LOGIC_1);
	t_up_down.write(SC_LOGIC_1);
	wait(1, SC_US);
		
	cout << " Stop reset and start " << endl;

	t_rst.write(SC_LOGIC_0);
	t_up_down.write(SC_LOGIC_1);
	wait(40, SC_US);
		
	cout << " Change direction " << endl;
		
	t_up_down.write(SC_LOGIC_0);
	wait(20, SC_US);
		
	cout << " Data load " << endl;

	t_data_in.write("1001");
	wait(20, SC_US);
	
	cout << " Write high " << endl;
	
	t_load.write(SC_LOGIC_1);
	wait(2, SC_US);
	
	cout << " Write low " << endl;
	
	t_load.write(SC_LOGIC_0);
	wait(9, SC_US);
		
	cout << " Resetting " << endl;

	t_rst.write(SC_LOGIC_1);
	wait(1, SC_US);
	
}

#ifdef MEMORY_RTL_H

void test_four_bit_counter::test_memory_rtl(void) {

	int i;
	
	cout << " Initial signal positioning " << endl;
	t_en.write(false);
	t_rd.write(false);
	t_wr.write(false);
	t_d_in.write("11111111");
	wait(1, SC_US);

	cout << " Enabling memory " << endl;
	t_en.write(true);

	cout << " Enabling write " << endl;
	t_wr.write(true);

	cout << " Write chaining " << endl;
	cout << " Writing at : " << 0 << endl;
	t_d_in.write("00000000");
	wait(1, SC_US);

	cout << " Writing at : " << 1 << endl;
	t_d_in.write("00000001");
	wait(1, SC_US);

	cout << " Writing at : " << 2 << endl;
	t_d_in.write("00000010");
	wait(1, SC_US);

	cout << " Writing at : " << 3 << endl;
	t_d_in.write("00000011");
	wait(1, SC_US);

	cout << " Writing at : " << 4 << endl;
	t_d_in.write("00000100");
	wait(1, SC_US);

	cout << " Writing at : " << 5 << endl;
	t_d_in.write("00000101");
	wait(1, SC_US);

	cout << " Writing at : " << 6 << endl;
	t_d_in.write("00000110");
	wait(1, SC_US);

	cout << " Writing at : " << 7 << endl;
	t_d_in.write("00000111");
	wait(1, SC_US);

	cout << " Writing at : " << 8 << endl;
	t_d_in.write("00001000");
	wait(1, SC_US);

	cout << " Writing at : " << 9 << endl;
	t_d_in.write("00001001");
	wait(1, SC_US);

	cout << " Writing at : " << 10 << endl;
	t_d_in.write("00001010");
	wait(1, SC_US);

	cout << " Writing at : " << 11 << endl;
	t_d_in.write("00001011");
	wait(1, SC_US);

	cout << " Writing at : " << 12 << endl;
	t_d_in.write("00001100");
	wait(1, SC_US);

	cout << " Writing at : " << 13 << endl;
	t_d_in.write("00001101");
	wait(1, SC_US);

	cout << " Writing at : " << 14 << endl;
	t_d_in.write("00001110");
	wait(1, SC_US);

	cout << " Writing at : " << 15 << endl;
	t_d_in.write("00001111");
	wait(1, SC_US);

	cout << " Enabling read " << endl;
	t_rd.write(true);
	t_wr.write(false);
	
	cout << " Read chaining " << endl;
	for(i=0; i<MEM_SIZE; i++) {
	
		cout << " Reading at : " << i << " : ";
		cout << t_d_out.read() << endl;
		wait(1, SC_US);

	}

	cout << " Disabling memory " << endl;
	t_en.write(false);
	t_rd.write(false);
	t_d_in.write("00000000");

}

void test_four_bit_counter::convertor(void) {

	t_addr = (sc_uint<4>)t_q;
	
	next_trigger(t_q.default_event());

}
	
#endif
