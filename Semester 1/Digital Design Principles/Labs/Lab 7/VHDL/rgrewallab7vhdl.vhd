library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity rgrewallab7vhdl is 
    port(
        Sw: in std_logic_vector(3 downto 0);
        led: out std_logic_vector(6 downto 0)
    );
end rgrewallab7vhdl;

architecture sevenSegmentDisplay of rgrewallab7vhdl is
    begin
        process(Sw) is
            begin
                case Sw is
                    when "0000" =>
                        led <= "0000001"; 
                    
                    when "0001" =>
                        led <= "1001111";
                    
                    when "0010" =>
                        led <= "0010010";
                    
                    when "0011" =>
                        led <= "0000110";
                    
                    when "0100" =>
                        led <= "1001100";
                    
                    when "0101" =>
                        led <= "0100100";
                    
                    when "0110" =>
                        led <= "0100000";
                    
                    when "0111" =>
                        led <= "0001111";
                    
                    when "1000" =>
                        led <= "0000000";
                    
                    when "1001" =>
                        led <= "0001100";
                    
                    when "1010" =>
                        led <= "0001000";
                    
                    when "1011" =>
                        led <= "1100000";
                    
                    when "1100" =>
                        led <= "0110001";
                    
                    when "1101" =>
                        led <= "1000010";
                    
                    when "1110" =>
                        led <= "0110000";
                    
                    when "1111" =>
                        led <= "0111000";
                    
                    when others =>
                        led <= "1111111";
                end case;
        end process;
end sevenSegmentDisplay;