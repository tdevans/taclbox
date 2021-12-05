LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ARCHITECTURE rtl OF test_entity IS
	TYPE t_slv8_vector is array (natural range <>) of std_logic_vector( 7 downto 0);
	TYPE t_mem is array (63 downto 0) of std_logic_vector(63 downto 0);
	TYPE t_unsigned_vector is array (integer range <>) of unsigned;
	TYPE t_signed_matrix is array (natural range <>, 0 to 15) of signed(7 downto 0);
	TYPE t_fixed_array is array (-10 to 10) of fixed(7 downto -8);

	SIGNAL bytes : t_slv8_vector(0 to 63);
BEGIN
	
END ARCHITECTURE rtl;