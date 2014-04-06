/**
 * 5.3.1 : Color Class
 */

/**
 * Includes
 */
#include <iostream>

/**
 * Using namespace
 */
using namespace std;

/** Enumeration type for Color **/
enum colorType {WHITE, RED, YELLOW, GREEN, BLUE };

/**
 * Color class definition
 */
class Color {

	protected:

		// Color fields
		colorType color;

	public:

		// Color constructor
		Color(colorType c) : color(c) { }

		/** Color methods **/
		
		// Color getter
		colorType getColor(void) const { return color; }

		// Color printer
		//
		// Please uncomment the version you want to use and comment the others
		//
		// Using the : first version will cause a polymorphed Color object to call this function
		//           : second version will cause a polymorphed Color object to call a new print function
		//           : third version will cause this class to become abstract, therefore no calls to
		//              this function from this object can be made

		// First version
		//
		//
		//void print() { cout << " Color : " << color << endl; }

		// Second version
		//
		//
		//virtual void print() { cout << " Color : " << color << endl; }

		// Third version
		//
		//
		virtual void print() = 0;
		
};