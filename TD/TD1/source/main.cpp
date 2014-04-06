#include "testbench/user.h"
#include "module/mod_10_counter.h"
#include <systemc.h>

int sc_main(int argc, char* argv[]) {

	sc_signal<double> p("period");
	sc_signal<bool> rst("rst"), u_d("u_d"), ld("ld");
	sc_signal<int> d_in("d_in"), q_out("q_out");

	cout << " Signals declared " << endl;

	sc_trace_file *tf = sc_create_vcd_trace_file("wave_mod_10_counter_unit");
	sc_write_comment(tf, "Simulation of modulo 10 counter");
	((vcd_trace_file*)tf)->set_time_unit(1, SC_NS);	// 10exp(-9) = 1 ns

	cout << " Trace file setup complete " << endl;

	user user0_inst("user0");
		user0_inst.period(p);
		user0_inst.reset(rst);
		user0_inst.up_down(u_d);
		user0_inst.load(ld);
		user0_inst.data_in(d_in);
	
	cout << " User instance setup complete " << endl;

	mod_10_counter mod_10_counter0_inst("mod_10_counter0");
		mod_10_counter0_inst.period(p);
		mod_10_counter0_inst.reset(rst);
		mod_10_counter0_inst.up_down(u_d);
		mod_10_counter0_inst.load(ld);
		mod_10_counter0_inst.data_in(d_in);
		mod_10_counter0_inst.q(q_out);

	cout << " Counter instance setup complete " << endl;

	sc_trace(tf, p, "p");
	sc_trace(tf, rst,"rst");
	sc_trace(tf, u_d,"u_d");
	sc_trace(tf, ld,"ld");
	sc_trace(tf, d_in,"d_in");
	sc_trace(tf, q_out,"q_out");

	cout << " Tracer position setup complete " << endl;

	cout << " Start simulation " << endl;

	sc_start(500, SC_NS);

	sc_close_vcd_trace_file(tf);

	system("pause");

	return 0;

}