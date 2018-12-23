`timescale 1ns / 1ps

module sign_extender_tb#(parameter in_bits = 16, parameter out_bits = 32) ();

reg   [ in_bits-1 : 0] in;
wire  [out_bits-1 : 0] out;

sign_extender extender_obj (.in(in), .out(out));

initial
begin
	#1 in = 16'b0101010101010101; 
	
	#1 in = 16'b1010101010101010; 
	
	#1 in = 16'b1111100011111111; 
	
	#1 in = 16'b0000011100000000; 
	
	#1 in = 16'b1111111111111111; 
end

initial
	#6 $finish;

	initial begin
	// Initialize Inputs
	in = 0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule

