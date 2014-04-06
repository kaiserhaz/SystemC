/**
 * 4.2 : SystemC Starting Point
 */

/** 
 * Includes
 */
#include <iostream>
#include <systemc.h>

/**
 * SystemC main
 */
int sc_main(int argc, char* argv[]) {

	if(argc == 1)

		cout << "No Argument ! " << endl;

	// ELABORATION Phase

	if(argc >= 2)

		cout << " First Argument : " << argv[1] << endl;

	if(argc >= 3)

		cout << " Second Argument : " << argv[2] << endl;

	sc_start(); // SIMULATION begins and ends in this function

	system("pause");

	return 0; // EXIT CODE (0 = success)
}
