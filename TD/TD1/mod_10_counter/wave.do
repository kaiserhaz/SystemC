### SystemC VCD to WLF conversion script ###
echo "SystemC VCD2WLF autoconverter converting : " $1
echo "do wave.do :" $1 ".vcd"

vcd2wlf $1.vcd $1.wlf
dataset open $1.wlf $1
add wave *
wave zoomfull