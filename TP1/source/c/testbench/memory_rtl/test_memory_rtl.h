#ifndef TEST_MEMORY_RTL_H
#define TEST_MEMORY_RTL_H

#include "systemc.h"
#include "../../module/memory_rtl.h"

SC_MODULE( test_memory_rtl ) {
	
	sc_out<bool> clk;
	sc_out<bool> enable;
	sc_out<bool> rd;
	sc_out<bool> wr;
	sc_out< sc_uint<ADDR_SIZE> > addr;
	sc_out< sc_lv<WORD_SIZE> > data_in;
	sc_in< sc_lv<WORD_SIZE> > data_out;
	
	sc_clock sys_clk1;
	
	SC_CTOR( test_memory_rtl ) : clk("clk"), enable("enable"),
	                             rd("rd"), wr("wr"), addr("addr"),
								 data_in("data_in"), data_out("data_out"),
								 sys_clk1("sys_clk1", 1, SC_US)
	{
		
		SC_THREAD( memory_testbench );
		
		SC_METHOD( sys_clk_process );
			sensitive << sys_clk1.default_event();
		
	}
	
	void sys_clk_process(void) {

		clk->write(sys_clk1.read());

	}

	void memory_testbench(void) {

		int i;
		
		cout << " Initial signal positioning " << endl;
		enable->write(false);
		rd->write(false);
		wr->write(false);
		addr->write(0);
		data_in->write("11111111");
		wait(10, SC_US);

		cout << " Enabling memory " << endl;
		enable->write(true);
		wait(1, SC_US);

		cout << " Enabling write " << endl;
		wr->write(true);
		wait(1, SC_US);

		cout << " Write chaining " << endl;
		cout << " Writing at : " << 0 << endl;
		addr->write(0);
		data_in->write("00000000");
		wait(1, SC_US);

		cout << " Writing at : " << 1 << endl;
		addr->write(1);
		data_in->write("00000001");
		wait(1, SC_US);

		cout << " Writing at : " << 2 << endl;
		addr->write(2);
		data_in->write("00000010");
		wait(1, SC_US);

		cout << " Writing at : " << 3 << endl;
		addr->write(3);
		data_in->write("00000011");
		wait(1, SC_US);

		cout << " Writing at : " << 4 << endl;
		addr->write(4);
		data_in->write("00000100");
		wait(1, SC_US);

		cout << " Writing at : " << 5 << endl;
		addr->write(5);
		data_in->write("00000101");
		wait(1, SC_US);

		cout << " Writing at : " << 6 << endl;
		addr->write(6);
		data_in->write("00000110");
		wait(1, SC_US);

		cout << " Writing at : " << 7 << endl;
		addr->write(7);
		data_in->write("00000111");
		wait(1, SC_US);

		cout << " Writing at : " << 8 << endl;
		addr->write(8);
		data_in->write("00001000");
		wait(1, SC_US);

		cout << " Writing at : " << 9 << endl;
		addr->write(9);
		data_in->write("00001001");
		wait(1, SC_US);

		cout << " Writing at : " << 10 << endl;
		addr->write(10);
		data_in->write("00001010");
		wait(1, SC_US);

		cout << " Writing at : " << 11 << endl;
		addr->write(11);
		data_in->write("00001011");
		wait(1, SC_US);

		cout << " Writing at : " << 12 << endl;
		addr->write(12);
		data_in->write("00001100");
		wait(1, SC_US);

		cout << " Writing at : " << 13 << endl;
		addr->write(13);
		data_in->write("00001101");
		wait(1, SC_US);

		cout << " Writing at : " << 14 << endl;
		addr->write(14);
		data_in->write("00001110");
		wait(1, SC_US);

		cout << " Writing at : " << 15 << endl;
		addr->write(15);
		data_in->write("00001111");
		wait(1, SC_US);

		cout << " Enabling read " << endl;
		rd->write(true);
		wr->write(false);
		wait(1, SC_US);

		cout << " Read chaining " << endl;
		for(i=0; i<MEM_SIZE; i++) {
		
			cout << " Reading at : " << i << " : ";
			addr->write((sc_uint<ADDR_SIZE>)i);
			cout << data_out->read() << endl;
			wait(1, SC_US);

		}

		cout << " Disabling memory " << endl;
		enable->write(false);
		rd->write(false);
		addr->write(0);
		data_in->write("00000000");

	}
	
};

#endif