library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_entity is
	port
	(
		i_clk : in std_logic;
		i_reset_n : in std_logic;
		i_a : in unsigned(3 downto 0);
		i_b : in unsigned(3 downto 0);
		o_y : out unsigned(3 downto 0)
	);
end entity test_entity;

architecture rtl of test_entity is

	signal y : unsigned(3 downto 0);

begin

	comb_0_logic:entity my_lib.test_entity_comb port map (i_a, i_b, y);
	
	process (i_reset_n, i_clk) is
	begin
		if (i_reset_n = '0') then
			o_y <= (others => '0');
		elsif (rising_edge(i_clk)) then
			o_y <= y;
		end if;
	end process;
	
end architecture rtl;