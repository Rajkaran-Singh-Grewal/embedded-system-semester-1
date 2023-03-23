module rgrewallab8verilog(input [5:0] S,
                    input [1:0] choice,
                    input P,
                    output reg [6:0]hex1,
                    output reg [6:0] hex2,
                    output reg [6:0] hex3,
                    output reg [6:0] hex4,
                    output reg led);
    reg [3:0] loadValue = 4'b0000;
    integer count = 0;
    always @(S,choice) begin
        if(!P) begin
            led = 1;
            count = count + 1;
            if(count == 0) begin
                case(choice)
                    2'b00: begin
                    end
                    2'b01: begin
                        loadValue[3] = loadValue[2];
                        loadValue[2] = loadValue[1];
                        loadValue[1] = loadValue[0];
                        loadValue[0] = S[0];
                    end
                    2'b10: begin
                        loadValue[0] = loadValue[1];
                        loadValue[1] = loadValue[2];
                        loadValue[2] = loadValue[3];
                        loadValue[3] = S[5]; 
                    end
                    2'b11: begin
                        loadValue[0] = S[1];
                        loadValue[1] = S[2];
                        loadValue[2] = S[3];
                        loadValue[3] = S[4];
                    end
                endcase  
            end
            hex1 = displaySevenSegment(loadValue[0]);
            hex2 = displaySevenSegment(loadValue[1]);
            hex3 = displaySevenSegment(loadValue[2]);
            hex4 = displaySevenSegment(loadValue[3]);
        end
        else begin
            led = 0;
            count = 0;
        end
    end
    function [6:0]displaySevenSegment(input character);
        case(character)
            0: begin
                displaySevenSegment = 7'b1000000;
            end
            1: begin
                displaySevenSegment = 7'b1111001;
            end
        endcase
    endfunction
endmodule