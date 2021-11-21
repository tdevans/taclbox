library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

architecture rtl of test_entity is
	type t_slv8_vector is array (natural range <>) of std_logic_vector( 7 downto 0);
	type t_mem is array (63 downto 0) of std_logic_vector(63 downto 0);
	type t_unsigned_vector is array (integer range <>) of unsigned;
	type t_signed_matrix is array (natural range <>, 0 to 15) of signed(7 downto 0);
	type t_fixed_array is array (-10 to 10) of fixed(7 downto -8);

	signal bytes : t_slv8_vector(0 to 63);
begin
	
end architecture rtl;