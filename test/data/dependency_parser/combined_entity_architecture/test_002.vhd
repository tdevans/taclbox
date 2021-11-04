library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_entity is
	port
	(
		i_clk     : in std_logic;
		i_reset_n : in std_logic;
		i_a       : in unsigned(3 downto 0);
		i_b       : in unsigned(3 downto 0);
		i_ctrl    : in std_logic;
		o_y       : out unsigned(3 downto 0)
	);
end entity test_entity;

architecture rtl of test_entity is

	signal y : unsigned(3 downto 0);

begin

	test_proc : process (i_clk) is
	begin
		if (rising_edge(i_clk)) then
			if (i_ctrl = '0') then
				o_y <= (others => '0');
			else
				o_y <= y;
			end if;
		end if;
	end process test_proc;
	
	y <= i_a + i_b;
	
end architecture rtl;