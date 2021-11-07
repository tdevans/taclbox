library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

architecture rtl of test_entity is
	type t_percent is range 0 to 100;
	type t_myint is range 2047 downto -2048;
	type t_myfloat_normal is range 0.0 to 106.71;
	type t_myfloat_scientific is range -1.0e6 to 3.14e5;
	type t_myfloat_scientific_negex is range -1.0e-2 to 1.0e-2;

	signal progress : t_percent;
begin

	process (i_reset_n, i_clk) is
	begin
		if (i_reset_n = '0') then
			progress <= 0;
		elsif (rising_edge(i_clk)) then
			if (i_en = '1') then
				progress <= progress + 1;
			end if;
		end if;
	end process;
	
end architecture rtl;
