library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity rgrewallab5vhdl is
    port(
        A: in std_logic_vector(3 downto 0);
        B: in std_logic_vector(3 downto 0);
        LED: out std_logic_vector(2 downto 0)
    );
end rgrewallab5vhdl;

architecture comparator of rgrewallab5vhdl is
    signal C: std_logic_vector(7 downto 0);
    signal D: std_logic_vector(3 downto 0);
    signal E: std_logic_vector(6 downto 0);
    begin
        process(A,B,C,D,E) is
        begin
            C(0) <= NOT(A(3)) AND B(3);
            C(1) <= A(3) AND NOT(B(3));
            C(2) <= NOT(A(2)) AND B(2);
            C(3) <= A(2) AND NOT(B(2));
            C(4) <= NOT(A(1)) AND B(1);
            C(5) <= A(1) AND NOT(B(1));
            C(6) <= NOT(A(0)) AND B(0);
            C(7) <= A(0) AND NOT(B(0));

            D(0) <= NOT(C(0) OR C(1));
            D(1) <= NOT(C(2) OR C(3));
            D(2) <= NOT(C(4) OR C(5));
            D(3) <= NOT(C(6) OR C(7));

            E(0) <= D(0) AND C(2);
            E(1) <= D(0) AND C(3);
            E(2) <= D(0) AND D(1) AND C(4);
            E(3) <= D(0) AND D(1) AND C(5);
            E(4) <= D(0) AND D(1) AND D(2) AND C(6);
            E(5) <= D(0) AND D(1) AND D(2) AND C(7);
            E(6) <= D(0) AND D(1) AND D(2) AND D(3);

            LED(0) <= C(0) OR E(0) OR E(2) OR E(4);
            LED(1) <= E(6);
            LED(2) <= C(1) OR E(1) OR E(3) OR E(5);
        end process;
end comparator;