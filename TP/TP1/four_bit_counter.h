#ifndef _SCGENMOD_four_bit_counter_
#define _SCGENMOD_four_bit_counter_

#include "systemc.h"

class four_bit_counter : public sc_foreign_module
{
public:
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> up_down;
    sc_in<sc_logic> load;
    sc_in<sc_lv<4> > data_in;
    sc_out<sc_lv<4> > q;


    four_bit_counter(sc_module_name nm, const char* hdl_name)
     : sc_foreign_module(nm),
       clk("clk"),
       rst("rst"),
       up_down("up_down"),
       load("load"),
       data_in("data_in"),
       q("q")
    {
        elaborate_foreign_module(hdl_name);
    }
    ~four_bit_counter()
    {}

};

#endif

