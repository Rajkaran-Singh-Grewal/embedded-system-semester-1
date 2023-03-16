library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity rgrewallab6vhdl is
    port(
        A: in std_logic_vector(3 downto 0);
        B: in std_logic_vector(3 downto 0);
        C: in std_logic;
        State: in std_logic;
        Hex1: out std_logic_vector(6 downto 0);
        Hex2: out std_logic_vector(6 downto 0);
        Sum: out std_logic_vector(3 downto 0);
        Carry: out std_logic_vector(3 downto 0)
    );
end rgrewallab6vhdl;

architecture adder of rgrewallab6vhdl is
    signal carryin: std_logic_vector(3 downto 0);
    begin
        process(A,B,C,State) is
            begin
                case State is
                    when '1' =>
                        Hex1 <= "0111000";
                        Hex2 <= "0001000";
                        carryin(0) <= C;
                        Sum(0) <= (A(0) XOR B(0)) XOR carryin(0);
                        carryin(1) <= ((A(0) XOR B(0)) and carryin(0)) or (A(0) and B(0));
                        
                        Sum(1) <= (A(1) XOR B(1)) XOR carryin(1);
                        carryin(2) <= ((A(1) xor B(1)) and carryin(1)) or (A(1) and B(1));
                        
                        Sum(2) <= (A(2) XOR B(2)) XOR carryin(2);
                        carryin(3) <= ((A(2) xor B(2)) and carryin(2)) or (A(2) and B(2));
                        
                        Sum(3) <= (A(3) XOR B(3)) XOR carryin(3);
                        Carry(0) <= ((A(3) xor B(3)) and carryin(3)) or (A(3) and B(3));
                        
                        
                    when '0' =>
                        Hex1 <= "1001000";
                        Hex2 <= "0001000";

                        Sum(0) <= A(0) XOR B(0);
                        Carry(0) <= A(0) AND B(0);
                        
                        Sum(1) <= A(1) XOR B(1);
                        Carry(1) <= A(1) AND B(1);
                        
                        Sum(2) <= A(2) XOR B(2);
                        Carry(2) <= A(2) AND B(2);
                        
                        Sum(3) <= A(3) XOR B(3);
                        Carry(3) <= A(3) AND B(3);
                    when others =>
                        Sum <= "0000";
                        Carry <= "0000";
                end case;
        end process;
end adder;