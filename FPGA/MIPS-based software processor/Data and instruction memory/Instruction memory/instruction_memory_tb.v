`timescale 1ns / 1ps

module instruction_memory_tb #(parameter n_bit = 31, parameter memory_size = 2047) ();

reg [n_bit : 0] in_addr;

wire [n_bit : 0] out_instruction;

instruction_memory_mips instruction_memory_mips_obj (.in_addr(in_addr), .out_instruction(out_instruction));

initial
begin
	#1
	in_addr = 32'd0;

	#1
	in_addr = 32'd1;
	
	#1
	in_addr = 32'd2;
	
	#1
	in_addr = 32'd3;
	
	#1
	in_addr = 32'd4;

	#1
	in_addr = 32'd5;
	
	#1
	in_addr = 32'd6;
	
	#1
	in_addr = 32'd7;
	
	#1
	in_addr = 32'd8;
	
	#1
	in_addr = 32'd9;
	
	#1
	in_addr = 32'd10;
end

initial
	#100 $finish;

	initial begin
	// Initialize Inputs

	in_addr = 32'd0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
