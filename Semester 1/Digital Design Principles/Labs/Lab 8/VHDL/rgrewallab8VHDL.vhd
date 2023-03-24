Library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity rgrewallab8VHDL is 
    port(
        S: in std_logic_vector(5 downto 0);
        choice: in std_logic_vector(1 downto 0);
        P: in std_logic;
        hex1: out std_logic_vector(6 downto 0);
        hex2: out std_logic_vector(6 downto 0);
        hex3: out std_logic_vector(6 downto 0);
        hex4: out std_logic_vector(6 downto 0);
        led: out std_logic 
    );
end rgrewallab8VHDL;

architecture shiftRegister of rgrewallab8VHDL is
    signal count: integer := 0;
    signal loadValue: std_logic_vector(3 downto 0) := "0000";
begin
    process(S,choice,count,loadValue,P) is 
    begin
        if(P = '0') then
            led <= '1';
            if(count < 1) then
                count <= count + 1;
                case choice is 
                    when "00" =>
                        NULL;
                    when "01" =>
                        loadValue(3) <= loadValue(2);
                        loadValue(2) <= loadValue(1);
                        loadValue(1) <= loadValue(0);
                        loadValue(0) <= S(0); 
                    when "10" =>
                        loadValue(0) <= loadValue(1);
                        loadValue(1) <= loadValue(2);
                        loadValue(2) <= loadValue(3);
                        loadValue(3) <= S(5);
                    when "11" =>
                        loadValue(0) <= S(1);
                        loadValue(1) <= S(2);
                        loadValue(2) <= S(3);
                        loadValue(3) <= S(4);
                    when others =>
                        NULL;
                end case;
            end if;
            case loadValue(0) is
                when '0' =>
                    hex1 <= "0000001";
                when '1' =>
                    hex1 <= "1001111";
                when others =>
                    hex1 <= "0000000";
            end case;
            case loadValue(1) is
                when '0' =>
                    hex2 <= "0000001";
                when '1' =>
                    hex2 <= "1001111";
                when others =>
                    hex2 <= "0000000";
            end case;
            case loadValue(2) is
                when '0' =>
                    hex3 <= "0000001";
                when '1' =>
                    hex3 <= "1001111";
                when others =>
                    hex3 <= "0000000";
            end case;
            case loadValue(3) is
                when '0' =>
                    hex4 <= "0000001";
                when '1' =>
                    hex4 <= "1001111";
                when others =>
                    hex4 <= "0000000";
            end case;
        else 
            led <= '0';
            count <= 0;
        end if;
    end process;
end shiftRegister;
