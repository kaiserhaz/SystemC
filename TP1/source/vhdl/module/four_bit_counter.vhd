library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- Entity description

entity four_bit_counter is
  port( clk     : in std_logic;
        rst     : in std_logic;
		up_down : in std_logic;
		load    : in std_logic;
		data_in : in std_logic_vector(3 downto 0);
		q       : out std_logic_vector(3 downto 0) );
end entity four_bit_counter;
	
-- Architecture description

architecture behaviour of four_bit_counter is
  
  begin
  
    four_bit_counter_process:process(clk, rst)
	
	  variable c : std_logic_vector(3 downto 0) := "0000";
	
	  begin
	  
	    if(rising_edge(rst) or rst = '1') then
		  
		   c := "0000";
		  
		  elsif(rising_edge(clk)) then
		  
		    if(load = '1') then
		  
		      c := data_in;
			
	      elsif(up_down = '0') then
		  
		      c := (c - 1);
			
		    else
		  
		      c := (c + 1);
			  
			  end if;
		  		
		  end if;
		  
		  q <= c;
    
	end process;
	
end architecture behaviour;