`timescale 1ns / 1ps

module mux_32_bit_tb #(parameter n_bit = 32) ();

reg in_control;

reg [n_bit : 0] in_0;
reg [n_bit : 0] in_1;

wire [n_bit : 0] out_result;

mux_32_bit mux_32_bit_obj (.in_control(in_control), .in_0(in_0), .in_1(in_1), .out_result(out_result));

initial
begin
	#1
	in_control = 0;
	in_0 = 32'ha;
	in_1 = 32'hb;
	
	#1
	in_control = 1;
	
	#1
	in_control = 0;
	in_0 = 32'h1;
	in_1 = 32'h2;
	
	#1
	in_control = 1;
	in_0 = 32'h3;
	in_1 = 32'h4;
	
end

initial
	#100 $finish;

	initial begin
	// Initialize Inputs
	
	in_control = 0;
	in_0 = 32'd0;
	in_1 = 32'd0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
