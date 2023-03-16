-- library initialize
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
-- end library initialize
-- entity initialize
entity rgrewallab3vhd is 
	port(SW0: in std_logic;
			Sw1: in std_logic;
			Sw2: in std_logic;
			Sw3: in std_logic;
			Sw4: in std_logic;
			Sw5: in std_logic;
			LEDR: out std_logic;
			LEDG: out std_logic);
end rgrewallab3vhd;
-- end entity initialize
-- architecture initialize 
architecture parkinglot of rgrewallab3vhd is
	begin
		-- and gate as LEDR will turn on when all switch is on.
		LEDR <= Sw0 and Sw1 and Sw2 and Sw3 and Sw4 and Sw5;
		-- nand gate as LEDG will turn on when there is atleast one switch is off
		LEDG <= not (Sw0 and Sw1 and Sw2 and Sw3 and Sw4 and Sw5);
end parkinglot;
-- end architecture initialize