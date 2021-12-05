-- Package Declaration Section
package example_package is
 
  constant c_PIXELS : integer := 65536;
 
  type t_FROM_FIFO is record
    wr_full  : std_logic;
    rd_empty : std_logic;
  end record t_FROM_FIFO;  
   
  component example_component is
    port (
      i_data  : in  std_logic;
      o_rsult : out std_logic); 
  end component example_component;
 
  function Bitwise_AND (
    i_vector : in std_logic_vector(3 downto 0))
    return std_logic;
   
end package example_package;
 
-- Package Body Section
package   body    example_package is
 
  function Bitwise_AND (
    i_vector : in std_logic_vector(3 downto 0)
    )
    return std_logic is
  begin
    return (i_vector (0) and i_vector (1) and i_vector (2) and i_vector (3));
  end;
 
end package body example_package;