`timescale 1ns/1ps
module rgrewallab9Verilog( input clk,
                            input timer,
                            input SwitchForJohnson,
                            input SwitchForTimer,
                            output reg [6:0] hex1,
                            output reg [6:0] hex2,
                            output reg [6:0] hex3,
                            output reg [6:0] hex4
                            );
    reg [3:0] clkLoadValue = 4'b0000;
    reg [3:0] timerLoadValue = 4'b0000;
    reg [3:0] loadValue;
    reg [26:0] counter = 0;
    reg clockOut = 0;
    
    always @(posedge(clk)) begin 
        if((clkLoadValue == 4'b0000) && !(SwitchForJohnson)) begin
            clkLoadValue = 4'b1000;
        end
        clkLoadValue = ringStateMachine(clkLoadValue, SwitchForJohnson);
    end
    
    always @(posedge timer) begin
        counter <= counter + 1;
        if(counter == 49_999_999) begin
            counter <= 0;
            clockOut <= 0;
        end
        else if (counter == 49_999_998) begin
            clockOut <= 1;
        end
        if(SwitchForTimer) begin
            if(clockOut) begin
                if((timerLoadValue == 4'b0000) && !(SwitchForJohnson)) begin
                    timerLoadValue = 4'b1000;
                end
                timerLoadValue = ringStateMachine(timerLoadValue, SwitchForJohnson);
            end
        end   
    end
    
    //display either timer load value or clk load value begin
    always @(clkLoadValue,timerLoadValue) begin
        if(SwitchForTimer) begin
            loadValue <= timerLoadValue;
        end
        else begin 
            loadValue <= clkLoadValue;
        end
        hex1 = displaySevenSegment(loadValue[0]);
        hex2 = displaySevenSegment(loadValue[1]);
        hex3 = displaySevenSegment(loadValue[2]);
        hex4 = displaySevenSegment(loadValue[3]); 
    end
    
    function [3:0] ringStateMachine(input [3:0] valueLoad, input SwitchForJohnson);
        if(SwitchForJohnson) begin
            case(valueLoad)
                4'b0000: begin
                    ringStateMachine = 4'b1000;
                end
                4'b1000: begin
                    ringStateMachine = 4'b1100;
                end
                4'b1100: begin
                    ringStateMachine = 4'b1110;
                end
                4'b1110: begin
                    ringStateMachine = 4'b1111;
                end
                4'b1111: begin
                    ringStateMachine = 4'b0111;
                end
                4'b0111: begin
                    ringStateMachine = 4'b0011;
                end
                4'b0011: begin
                    ringStateMachine = 4'b0001;
                end
                4'b0001: begin
                    ringStateMachine = 4'b0000;
                end
                default: begin
                    ringStateMachine = 4'b0000;
                end
            endcase
        end
        else begin
            case(valueLoad)
                4'b1000: begin
                    ringStateMachine = 4'b0100;
                end
                4'b0100: begin
                    ringStateMachine = 4'b0010;
                end
                4'b0010: begin
                    ringStateMachine = 4'b0001;
                end
                4'b0001: begin
                    ringStateMachine = 4'b1000;
                end
                default: begin
                    ringStateMachine = 4'b1000;
                end
            endcase
        end
    endfunction
    
    function [6:0] displaySevenSegment(input character);
        case(character)
            0: begin
                displaySevenSegment = 7'b0000001;
            end
            1: begin
                displaySevenSegment = 7'b1001111;
            end
            default: begin
                displaySevenSegment = 7'b1111111;
            end
        endcase
    endfunction
endmodule