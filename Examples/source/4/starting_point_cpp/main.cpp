/**
 * 4.1 : C++ Starting Point
 */

/** 
 * Includes
 */
#include <iostream>

/**
 * Standard C++ main
 */
int main(int argc, char* argv[]) {

	if(argc == 1)

		std::cout << " No Argument ! " << std::endl;

	if(argc >= 2)

		std::cout << " First Argument : " << argv[1] << std::endl;

	if(argc >= 3)

		std::cout << " Second Argument : " << argv[2] << std::endl;

	// Body of Program

	system("pause");

	return 0; // EXIT CODE (0 = success)

}
