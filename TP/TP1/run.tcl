# Quit simulation
quit -sim

# Check if library exists. If so, delete it then recreate it
if [file exists work] {
    vdel -all
}

vlib work

# Compile the VHDL source files
vcom -93 source/vhdl/module/four_bit_counter.vhd
vcom -93 source/vhdl/testbench/test_four_bit_counter.vhd

# Test the input argument to see which test needs to be run
if {$1 == "v"} {

	# Start RTL simulation
	vsim work.test_four_bit_counter(testbench)
	
	# Display wave
	add wave *

	# Run simulation
	set StdArithNoWarnings 1
	run 100 us
	
} elseif {$1 == "c"} {

	# Generate foreign module declaration
	scgenmod source/vhdl/module/four_bit_counter > four_bit_counter.h

	# Compile and link C source files
	sccom -g source/c/testbench/four_bit_counter/test_four_bit_counter.cpp
	sccom -link

	# Start mixed simulation
	vsim work.test_four_bit_counter

	# Display Wave
	add wave *

	# Run simulation
	set StdArithNoWarnings 1
	run 100 us
} else {
    
    # Error message
    echo ""
    echo ""
    echo ""
    echo " Error! "
    echo ""
    echo ""
    echo ""
    echo " Please indicate your simulation choice as argument : "
    echo "   v - VHDL simulation "
    echo "   c - SystemC simulation "
        
}