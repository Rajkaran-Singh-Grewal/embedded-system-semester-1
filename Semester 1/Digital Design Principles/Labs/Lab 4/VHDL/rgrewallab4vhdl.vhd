library IEEE;
use ieee.STD_LOGIC_1164.all;

entity rgrewallab4vhdl is
    port(
        X: in std_logic_vector(2 downto 0);
        Y: out std_logic_vector(7 downto 0));
end rgrewallab4vhdl;

architecture octalDecoder of rgrewallab4vhdl is
   begin
        process(X) is
            begin
		        case X is
			        when "000" => Y <= "00000001";
			        when "001" => Y <= "00000010";
			        when "010" => Y <= "00000100";
			        when "011" => Y <= "00001000";
			        when "100" => Y <= "00010000";
			        when "101" => Y <= "00100000";
			        when "110" => Y <= "01000000";
			        when "111" => Y <= "10000000";
	            end case;
        end process;
end octalDecoder;
