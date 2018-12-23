`timescale 1ns / 1ps

module program_counter_tb ();

reg  clk;
reg  [31 : 0] instruction;
reg  is_jump;
reg  reset;
wire [31 : 0] ptr;

program_counter_mips program_counter_mips_obj (.clk(clk), .instruction(instruction), .is_jump(is_jump), .ptr(ptr), .reset(reset));

initial
begin
	#1 instruction = 0'd0;
	is_jump = 0;
	reset = 1;
	clk = 1;
	
	#1 clk = 0;
	reset = 0;
	
	#1 clk = 1;
	#1 clk = 0;
	
	#1 clk = 1;
	#1 clk = 0;
	
	#1 instruction = 32'b10101010_10101010101010101010101010;
	is_jump = 1;
	clk = 1;
	
	#1 clk = 0;
	is_jump = 0;
	
	#1 clk = 1;
	#1 clk = 0;
	
	#1 clk = 1;
	#1 clk = 0;
	
	#1 reset = 1;
	clk = 1;
	
	#1 clk = 0;
	reset = 0;

end

initial
	#100 $finish;

	initial begin
	// Initialize Inputs
	clk = 0;
	instruction = 32'd0;
	is_jump = 0;
	reset = 0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
