module rgrewallab6verilog(input [3:0]A,
                        input [3:0]B,
                        input C, 
                        input State,
                        output reg [6:0] hex1,
                        output reg [6:0] hex2,
                        output reg[3:0] sum,
                        output reg[3:0] carry);
        integer i;
        reg carryin;
        reg [1:0] adder;
        always @(A,B,C,State) begin
            carryin = C;
            case(State)
                1'b1:begin 
                    hex1 = 7'b0111000;
                    hex2 = 7'b0001000;
                    for(i = 0;i<4;i =  i+1) begin
                        adder =  fullAdder(A[i],B[i],carryin);
                        carryin = adder[1];
                        sum[i] = adder[0];   
                    end
                    carry[0] = carryin;
                end
                1'b0: begin
                    hex1 = 7'b1001000;
                    hex2 = 7'b0001000;
                    for(i =0;i<4;i=i+1) begin
                        adder = halfAdder(A[i],B[i]);
                        sum[i] = adder[0];
                        carry[i] = adder[1];
                    end
                end
                default: begin
                    sum = 4'b0000;
                    carry = 4'b0000;
                end
            endcase
        end
    function [1:0] halfAdder(input A,B);
        reg Sum = A ^ B;
        reg Carry = A && B;
        halfAdder[0] = Sum;
        halfAdder[1] = Carry;
    endfunction
    function [1:0] fullAdder(input A,B,Carryin);
        reg Sum = A ^ B ^ Carryin;
        reg Carryout = (A ^ B && Carryin) || (A && B);
        fullAdder[0] = Sum;
        fullAdder[1] = Carryout;
    endfunction
endmodule