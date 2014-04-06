library ieee;
use ieee.std_logic_1164.all;

-- Entity description

entity test_four_bit_counter is
end entity test_four_bit_counter;

-- Architecture description

architecture testbench of test_four_bit_counter is
  
  -- Component here
  
  component four_bit_counter is
    port( clk     : in std_logic;
          rst     : in std_logic;
		      up_down : in std_logic;
		      load    : in std_logic;
		      data_in : in std_logic_vector(3 downto 0);
		      q       : out std_logic_vector(3 downto 0) );
  end component;
  
  -- Elaborate here
  
  for DUT:four_bit_counter use entity work.four_bit_counter(behaviour);
  
  -- Sigs here
  
  signal t_clk, t_rst, t_up_down, t_load : std_logic := '0';
  signal t_data_in, t_q : std_logic_vector(3 downto 0);
  
  begin
    
    DUT:four_bit_counter port map(t_clk, t_rst, t_up_down, t_load, t_data_in, t_q);
    
    sys_clk0:process
      begin
        t_clk <= not t_clk;
        wait for 500 ns;
    end process;
    
    t_rst <= '1', '0' after 1 us, '1' after 92 us;
	  t_up_down <= '1', '0' after 41 us;	
	  t_load <= '1' after 81 us, '0' after 83 us;
	  t_data_in <= "1001" after 61 us;
    
end testbench;


