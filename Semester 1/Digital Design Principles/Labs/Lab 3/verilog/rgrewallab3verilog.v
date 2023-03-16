// initialize module 
module rgrewallab3verilog(input Sw0,
									input Sw1,
									input Sw2,
									input Sw3,
									input Sw4,
									input Sw5,
									output LEDR,
									output LEDG); 

// initalize and gate LEDR which will turn on when all switch is turned on
assign LEDR = Sw0 & Sw1 & Sw2 & Sw3 & Sw4 & Sw5;
// initialize nand gate LEDG which will turn on when atleast one switch is turned 
// off
assign LEDG = !(Sw0 & Sw1 & Sw2 & Sw3 & Sw4 & Sw5);
endmodule
// end initilize module