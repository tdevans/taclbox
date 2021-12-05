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
		o_y0 : out unsigned(3 downto 0);
		o_y1 : out unsigned(3 downto 0)
	);
end entity test_entity;

architecture rtl of test_entity is

	component test_entity_comb_0 is
		port
		(
			i_a : in unsigned(3 downto 0);
			i_b : in unsigned(3 downto 0);
			o_y : out unsigned(3 downto 0)
		);
	end component test_entity_comb_0;

	component test_entity_comb_1 is
		generic
		(
			g_width : integer
		);
		port
		(
			i_a : in unsigned(g_width - 1 downto 0);
			i_b : in unsigned(g_width - 1 downto 0);
			o_y : out unsigned(g_width - 1 downto 0)
		);
	end compoennt test_entity_comb_1;

	signal y0 : unsigned(3 downto 0);
	signal y1 : unsigned(3 downto 0);

begin

	comb_0_logic : test_entity_comb_0
	port map
	(
		i_a => i_a,
		i_b => i_b,
		o_y => y0
	);

	comb_1_logic : test_entity_comb_1
	generic map(g_width => 4)
	port map
	(
		i_a => i_a,
		i_b => i_b,
		o_y => y1
	);
	
	process (i_reset_n, i_clk) is
	begin
		if (i_reset_n = '0') then
			o_y0 <= (others => '0');
			o_y1 <= (others => '0');
		elsif (rising_edge(i_clk)) then
			o_y0 <= y0;
			o_y1 <= y1;
		end if;
	end process;
	
end architecture rtl;