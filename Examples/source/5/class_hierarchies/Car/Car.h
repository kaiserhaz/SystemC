/**
 * 5.3.2 : Car Class
 */

/**
 * Includes
 */
#include <iostream>
#include "../Color/Color.h"

/**
 * Using namespace
 */
using namespace std;

/**
 * Car class definition
 */
class Car : public Color {

	private:

		// Car fields
		int seat;

	public:

		// Car constructor
		Car(colorType c, int s) : Color(c), seat(s) { }

		/** Car methods **/

		// Car seat getter
		int getSeat(void) const{ return seat; }

		// Car printer
		void print() {

			cout << " Car Seat : " << seat;
			cout << " and Color : " << color << endl;

		}

};