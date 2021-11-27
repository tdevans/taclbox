library ieee;
use ieee.std_logic_1164.all;

entity top is
	port
	(
		i_clk : in std_logic;
		i_reset_n : in std_logic;
		i_a : in std_logic_vector(7 downto 0);
		i_b : in std_logic_vector(7 downto 0);
		o_y : out std_logic_vector(7 downto 0)
	);
end entity top;

architecture rtl of top is

	signal y : std_logic_vector(7 downto 0);
	
begin
	
	top_comb : entity work.top_comb
	port map
	(
		i_a => i_a,
		i_b => i_b,
		o_y => y
	);
	
	process (i_reset_n, i_clk) is
	begin
		if (i_reset_n = '0') then
			o_y <= (others => '0');
		elsif (rising_edge(i_clk)) then
			o_y <= y;
		end if;
	end process;
end architecture rtl;