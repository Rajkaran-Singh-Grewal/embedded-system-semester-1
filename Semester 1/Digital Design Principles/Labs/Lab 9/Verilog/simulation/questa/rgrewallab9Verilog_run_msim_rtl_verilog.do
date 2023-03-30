transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Embedded\ Systems/Semester\ 1/Digital\ Design\ Principles/Labs/Lab\ 9/Verilog {C:/Embedded Systems/Semester 1/Digital Design Principles/Labs/Lab 9/Verilog/rgrewallab9Verilog.v}

