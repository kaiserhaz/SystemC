/**
 * 5.3.3 : Class Hierarchies Example
 */

/**
 * Includes
 */
#include <iostream>
#include "Car/Car.h"

/**
 * Using namespace
 */
using namespace std;

/**
 * Main
 */
int main() {

	// This may cause error if we use the third version of the print method in Color.h
	//  since an abstract class cannot be instanciated
	// Comment it when using the third version and use the line below.
	//Color *cl = new Color(RED);
	Color *cl;

	Car car(WHITE, 3);

	// This may cause error if we use the third version of the print method in Color.h
	// Comment it when using the third version
	//cl->print();

	car.print();

	cl = &car;

	cl->print();

	system("pause");

	return 0;
}