module rgrewallab10Verilog(input CLK,
                            input pushButton1,
                            input pushButton2,
                            input pushButton3,
                            input pushButton4,
                            output reg [6:0] hex1,
                            output reg [6:0] hex2,
                            output reg [6:0] hex3,
                            output reg [6:0] hex4,
                            output reg [6:0] hex5,
                            output reg [6:0] hex6,
                            output reg led
                            );
    wire clockPhase;
    reg [3:0] counter = 4'b0000;
    reg [3:0] counter2 = 4'b1000;
    reg pushState1 = 0;
    reg pushState2 = 0;
    reg pushState3 = 0;
    reg pushState4 = 0;
    clockCycle colock(.CLK(CLK),
                        .clockCycle(clockPhase));
    always @(posedge clockPhase) begin
        counter = counter + 1;
        counter2 = counter2 + 1;
        if(counter > 15) begin
            counter = 0;
            pushState1 = 0;
            pushState3 = 0;
        end
        if(counter > 8) begin
            pushState1 = 0;
            pushState3 = 0;
        end
        if(counter2 > 15) begin
            counter2 = 0;
            pushState2 = 0;
            pushState4 = 0;
        end
        if(counter2 > 8) begin
            pushState2 = 0;
            pushState4 = 0;
        end
        
        if(pushButton1 == 0) begin
            pushState1 = 1;
            led = 1;
        end
        else begin
            led = 0;
        end

        if(pushButton2 == 0) begin
            pushState2 = 1;
            led = 1;
        end
        else begin
            led = 0;
        end

        if(pushButton3 == 0) begin
            pushState3 = 1;
            led = 1;
        end
        else begin
            led = 0;
        end

        if(pushButton4 == 0) begin
            pushState4 = 1;
            led = 1;
        end
        else begin
            led = 0;
        end

        hex1 = displaySevenSegment(counter);
        hex2 = displaySevenSegment(counter2);
        hex3 = displaySevenSegment2(pushState1,counter);
        hex4 = displaySevenSegment2(pushState2, counter2);
        hex5 = displaySevenSegment2(pushState3, counter);
        hex6 = displaySevenSegment2(pushState4, counter2);
    end
    function [6:0] displaySevenSegment(input [3:0] counter);
    case(counter)
        4'b0000: begin
            displaySevenSegment = 7'b0100001;
        end
        4'b0001: begin 
            displaySevenSegment = 7'b0100001;
        end
        4'b0010: begin
            displaySevenSegment = 7'b0100001;
        end
        4'b0011: begin
            displaySevenSegment = 7'b0100001;
        end
        4'b0100: begin
            displaySevenSegment = 7'b0100001;
        end
        4'b0101: begin
            displaySevenSegment = 7'b1011000;
        end
        4'b0110: begin
            displaySevenSegment = 7'b1011000;
        end
        4'b0111: begin
            displaySevenSegment = 7'b1011000;
        end
        default: begin
            displaySevenSegment = 7'b1111010;
        end
    endcase
   endfunction
    function [6:0] displaySevenSegment2(input pushState,input [4:0] counter);
        if(pushState == 0) begin
            displaySevenSegment2 = 7'b1111111;
        end
        else begin
            case(counter)
                4'b0000:begin
                    displaySevenSegment2 = 7'b0001111;
                end
                4'b0001: begin
                    displaySevenSegment2 = 7'b0100000;
                end
                4'b0010: begin
                    displaySevenSegment2 = 7'b0100100;
                end
                4'b0011: begin
                    displaySevenSegment2 = 7'b1001100;
                end
                4'b0100: begin
                    displaySevenSegment2 = 7'b0000110;
                end
                4'b0101: begin
                    displaySevenSegment2 = 7'b0010010;
                end
                4'b0110: begin
                    displaySevenSegment2 = 7'b1001111;
                end 
                4'b0111: begin
                    displaySevenSegment2 = 7'b0000001;
                end
                default: begin
                    displaySevenSegment2 = 7'b0000000;
                end
            endcase
        end
    endfunction
endmodule
module clockCycle(input CLK,
                    output reg clockCycle);
    reg [26:0] counter = 0;
    always @(posedge CLK) begin
        counter = counter + 1;
        if(counter == 49_999_999) begin
            counter = 0;
            clockCycle = 0;
        end
        else if(counter == 49_999_998) begin
            clockCycle = 1;
        end
    end
endmodule