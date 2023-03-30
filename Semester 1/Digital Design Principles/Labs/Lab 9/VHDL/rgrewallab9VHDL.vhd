library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
entity rgrewallab9VHDL is
    port(
        clk: in std_logic;
        timer: in std_logic;
        SwitchForJohnson: in std_logic;
        SwitchForTimer: in std_logic;
        hex1: out std_logic_vector(6 downto 0);
        hex2: out std_logic_vector(6 downto 0);
        hex3: out std_logic_vector(6 downto 0);
        hex4: out std_logic_vector(6 downto 0)
    );
end rgrewallab9VHDL;

architecture ringCounter of rgrewallab9VHDL is
    signal clkLoadValue: std_logic_vector(3 downto 0) := "1000";
    signal timerLoadValue: std_logic_vector(3 downto 0) := "0000";
    signal loadValue: std_logic_vector(3 downto 0);
    signal counter: std_logic_vector(0 to 26);
    signal clockOut: std_logic := '0';
    function ringStateMachine(valueLoad: std_logic_vector(3 downto 0); SwitchForJohnson: std_logic)
    return std_logic_vector is
        variable returnValue: std_logic_vector(3 downto 0);
    begin
        if((SwitchForJohnson = '1')) then
            case valueLoad is
                when "0000" =>
                    returnValue := "1000";
                when "1000" =>
                    returnValue := "1100";
                when "1100" =>
                    returnValue := "1110";
                when "1110" =>
                    returnValue := "1111";
                when "1111" =>
                    returnValue := "0111";
                when "0111" =>
                    returnValue := "0011";
                when "0011" =>
                    returnValue := "0001";
                when "0001" =>
                    returnValue := "0000";
                when others =>
                    returnValue := "0000";
            end case;
        else
            case valueLoad is
                when "1000" =>
                    returnValue := "0100";
                when "0100" =>
                    returnValue := "0010";
                when "0010" =>
                    returnValue := "0001";
                when "0001" =>
                    returnValue := "1000";
                when others =>
                    returnValue := "1000";
            end case;
        end if;
        return returnValue;
    end function;
    function displaySevenSegment(character: std_logic) return std_logic_vector is
        variable returnValue: std_logic_vector(6 downto 0);
    begin
        case character is
            when '0' =>
                returnValue := "0000001";
            when '1' =>
                returnValue := "1001111";
            when others =>
                returnValue := "1111111";
        end case;
        return returnValue;
    end function;
    begin
        
        process(clk) is
        begin
            if(rising_edge(clk)) then
                if((clkLoadValue = "0000") and Not(SwitchForJohnson = '1')) then
                    clkLoadValue <= "1000";
                end if;
                if(Not(SwitchForTimer = '1')) then
                    clkLoadValue <= ringStateMachine(clkLoadValue, SwitchForJohnson);
                end if;
            end if;
        end process;

        process(timer) is
        begin
            if(rising_edge(timer)) then
                counter <= counter + 1;
                if(counter = 49_999_999) then
                    counter <= "000000000000000000000000000";
                    clockOut <= '0';
                elsif(counter = 49_999_998) then
                    clockOut <= '1';
                end if;
                if((SwitchForTimer = '1')) then
                    if((clockOut = '1')) then
                        if((timerLoadValue = "0000") and not((SwitchForJohnson = '1'))) then
                            timerLoadValue <= "1000";
                        end if;
                        timerLoadValue <= ringStateMachine(timerLoadValue, SwitchForJohnson);
                    end if;
                end if;
            end if;
        end process;
        
        process(clkLoadValue, timerLoadValue) is
        begin
            if((SwitchForTimer = '1')) then
                loadValue <= timerLoadValue;
            else 
                loadValue <= clkLoadValue;
            end if;
            hex1 <= displaySevenSegment(loadValue(0));
            hex2 <= displaySevenSegment(loadValue(1));
            hex3 <= displaySevenSegment(loadValue(2));
            hex4 <= displaySevenSegment(loadValue(3));
        end process;
end ringCounter;