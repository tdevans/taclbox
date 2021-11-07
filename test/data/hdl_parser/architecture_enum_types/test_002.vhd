library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

architecture rtl of test_entity is
	type t_state is (
		s_idle,
		s_active,
		s_wait
	);
	
	signal state : t_state;
begin

	process (i_reset_n, i_clk) is
	begin
		if (i_reset_n = '0') then
			state <= s_idle;
		elsif (rising_edge(i_clk)) then
			case (state) is
				when s_idle =>
					if (i_en = '1') then
						state <= s_active;
					end if;
				
				when s_active =>
					state <= s_wait;
				
				when s_wait =>
					if (i_ready = '1') then
						state <= s_idle;
					end if;
			end case;
		end if;
	end process;
	
end architecture rtl;