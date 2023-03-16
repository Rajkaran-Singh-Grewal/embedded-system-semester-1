module rgrewallab7verilog(input [3:0] Sw,output reg [6:0] led);
always @(Sw) begin
    case(Sw)
        4'b0000: begin
            led = 7'b0000001; 
        end 
        4'b0001: begin
            led = 7'b1001111;
        end
        4'b0010: begin
            led = 7'b0010010;
        end 
        4'b0011: begin
            led = 7'b0000110;
        end
        4'b0100: begin
            led = 7'b1001100;
        end 
        4'b0101: begin
            led = 7'b0100100;
        end
        4'b0110: begin
            led = 7'b0100000;
        end 
        4'b0111: begin
            led = 7'b0001111;
        end
        4'b1000: begin
            led = 7'b0000000;
        end 
        4'b1001: begin
            led = 7'b0001100;
        end
        4'b1010: begin
            led = 7'b0001000;
        end 
        4'b1011: begin
            led = 7'b1100000;
        end
        4'b1100: begin
            led = 7'b0110001;
        end 
        4'b1101: begin
            led = 7'b1000010;
        end
        4'b1110: begin
            led = 7'b0110000;
        end 
        4'b1111: begin
            led = 7'b0111000;
        end
        default: begin
            led = 7'b1111111;
        end
    endcase
end
endmodule