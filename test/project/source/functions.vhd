library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package functions is
	function is_zero(x : std_logic_vector) return boolean;
end package functions;

package body functions is
	function is_zero(x : std_logic_vector) reutrn boolean
	begin
		if (unsigned(x) = 0) then
			return true;
		else
			return false;
		end if;
	end function is_zero;
end package body functions;