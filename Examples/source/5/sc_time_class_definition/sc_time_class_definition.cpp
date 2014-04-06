/**
 * 5.1 : sc_time Class Definition
 */

/**
 * Includes
 */
#include <systemc.h>

/**
 * Main
 */
int sc_main(int argc, char* argv[]) {

	// Important : this will determine the resolution for the display
	//  when using double format. If not, it may default to the lowest
	//  resolution there is, which is SC_FS (femtoseconds)
	sc_set_time_resolution(1, SC_NS);

	// sc_time object declaration
	sc_time a = sc_time(2.5, SC_US);

	// Different printouts for the sc_time object
	cout << " to_string()  : " << a.to_string() << endl;
	cout << " to_double()  : " << a.to_double() << endl;
	cout << " to_seconds() : " << a.to_seconds() << endl;

	system("pause");

	return 0;

}
