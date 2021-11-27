library ieee;
use ieee.std_logic_1164.all;

entity top_comb is
	port
	(
		i_a : in std_logic_vector(7 downto 0);
		i_b : in std_logic_vector(7 downto 0);
		o_y : out std_logic_vector(7 downto 0)
	);
end entity top_comb;

architecture rtl of top is
begin
	o_y <= i_a xor i_b;
end architecture rtl;