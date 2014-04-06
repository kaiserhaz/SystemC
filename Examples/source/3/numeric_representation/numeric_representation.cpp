/**
 * 3.1 : Numeric Representation
 */

/** 
 * Includes
 */
#include <systemc.h>
#include <iostream>

/**
 * Main function
 */
int sc_main(int argc, char* argv[]) {

	sc_int<8> rx_data = 106;
	sc_int<4> tx_buf = -5;

	// Display an sc_int using different numeric representations. In general, we use the 'to_string' method

	cout<< " Default               : rx_data = " << rx_data.to_string()           << endl; // Default representation
	cout<< " Binary                : rx_data = " << rx_data.to_string(SC_BIN)     << endl; // Binary representation
	cout<< " Binary unsigned       : rx_data = " << rx_data.to_string (SC_BIN_US) << endl; // Unsigned binary representation
	cout<< " Binary sign magnitude : rx_data = " << rx_data.to_string(SC_BIN_SM)  << endl; // Binary sign maggnitude repr.
	cout<< " Octal                 : tx_buf  = " << tx_buf.to_string (SC_OCT)     << endl; // Octal representation
	cout<< " Hexadecimal           : tx_buf  = " << tx_buf.to_string (SC_HEX)     << endl; // Hexadecimal representation
	cout<< " Decimal               : tx_buf  = " << tx_buf.to_string (SC_DEC)     << endl; // Decimal representation

	cout<< " ----------------------------- " << endl;

	cout<< " Binary without base      : rx_data = " << rx_data.to_string(SC_BIN, false) << endl; // Binary, base toggled off
	cout<< " Hexadecimal without base : tx_buf  = " << tx_buf.to_string (SC_HEX, false) << endl; // Hex, base toggled off
	cout<< " Decimal without base     : tx_buf  = " << tx_buf.to_string (SC_DEC, false) << endl; // Decimal, base toggled off

	system("pause");

	return 0;

}