/**
 * 5.2 : Simulation Example
 */

/**
 * Includes
 */
#include <systemc.h>

/**
 * Main
 */
int sc_main(int argc, char* argv[]) {

	// Sets the global simulation time resolution. Only called once
	sc_set_time_resolution(1, SC_MS);

	cout << " Time resolution is   : " << sc_get_time_resolution()   << endl;
	cout << " Current time         : " << sc_time_stamp()            << endl;
	cout << " Delta cycles passed  : " << sc_delta_count()           << endl;
	cout << " sc_start() ... "                                       << endl;

	// Simulate for 2 hours
	sc_start(7200, SC_SEC);

	cout << " Current time         : " << sc_time_stamp()  << endl;
	cout << " Delta cycles passed  : " << sc_delta_count() << endl;

	// Get simulation time
	sc_time t_ = sc_time_stamp();

	double t = t_.to_double();

	cout << " sc_time_stamp        : " << t << endl;

	// Convert into HH:MM:SS format
	unsigned hours = int(t / 3600000.0);
	t -= 3600000.0*hours;
	cout << " Hours                : " << hours << endl;

	unsigned minutes = int(t / 60000.0);
	t -= 60000.0*minutes;
	cout << " Minutes              : " << minutes << endl;

	double seconds = t;
	cout << " Seconds              : " << seconds << endl;

	cout << " " << hours << ":" << minutes << ":" << seconds << endl;

	// Stop simumation
	sc_stop();

	system("pause");

	return 0;

}
