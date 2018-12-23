`timescale 1ns / 1ps

module data_memory_tb__ #(parameter n_bit = 31, parameter memory_size = 2047) ();

reg in_clk, in_we;			// in_we - write enable to memory

reg [n_bit : 0] in_addr;

reg [n_bit : 0] in_write_data;

wire [n_bit : 0] out_read_data;

data_memory_mips data_memory_mips_obj (.in_clk(in_clk), .in_we(in_we), .in_addr(in_addr), .in_write_data(in_write_data), .out_read_data(out_read_data));

initial
begin
	#1
	in_clk = 1;
	in_we = 1;
	in_addr = 32'd123;
	in_write_data = 32'hAAAA;
	
	#1
	in_clk = 0;
	
	#1
	in_clk = 1;
	in_we = 1;
	in_addr = 32'd2000;
	in_write_data = 32'd322228;
	
	
	#1
	in_clk = 0;	
	
	#1
	in_clk = 1;
	in_we = 0;
	in_addr = 32'd123;
	in_write_data = 32'h0;
	
	#1
	in_clk = 0;
	
	#1
	in_clk = 1;
	in_we = 0;
	in_addr = 32'd2000;
	in_write_data = 32'h0;
	

end

initial
	#100 $finish;

	initial begin
	// Initialize Inputs
	
	in_we = 0;
	in_clk = 0;
	in_addr = 32'd0;
	in_write_data = 32'd0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
