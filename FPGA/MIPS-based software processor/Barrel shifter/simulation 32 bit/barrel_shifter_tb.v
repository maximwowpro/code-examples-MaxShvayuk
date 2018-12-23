`timescale 1ns / 1ps

module barrel_shifter_tb#(parameter n = 31) ();

reg  [n : 0] in;
reg  [4 : 0] sl;		/* means "shift lenght"	    		*/
wire [n : 0] out;
reg  left_or_right;		/* left == 0 , right == 1   		*/
reg  logic_shift;		/* 1 to select one of kinds of shifts 	*/
reg  rotate_shift;
reg  ariphmethic_shift;


reg  [4 : 0] cnt;		/* counter of for-loop	    		*/

barrel_shifter shifter_obj(.in (in), .sl (sl), .left_or_right (left_or_right), 
			   .logic_shift (logic_shift), .rotate_shift (rotate_shift), 
			   .ariphmethic_shift (ariphmethic_shift), .out (out));

initial
begin
	/* logic shift test 	*/
	#1 in = 32'b11111111111111110000000000000000; 
	sl  = 5'b00000; 
	left_or_right = 1'b0; 
	logic_shift = 1;
	rotate_shift = 0;
	ariphmethic_shift = 0;
		for (cnt = 5'd0; cnt < 5'd9; cnt = cnt + 5'd1)
			#1 sl = cnt;
	
	#1 sl = 5'b00000; 
	left_or_right = 1'b1; 
	logic_shift = 1;
	rotate_shift = 0;
	ariphmethic_shift = 0;
		for (cnt = 5'd0; cnt < 5'd9; cnt = cnt + 5'd1)
			#1 sl = cnt;
	
	/* rotate shift test 	*/
	#1 sl = 5'b00000; 
	left_or_right = 1'b0; 
	logic_shift = 0;
	rotate_shift = 1;
	ariphmethic_shift = 0;
		for (cnt = 5'd0; cnt < 5'd8; cnt = cnt + 5'd1)
			#1 sl = cnt;
	
	#1 in = 32'b01111111111111110000000000001010; 
	sl = 5'b00000; 
	left_or_right = 1'b1; 
	logic_shift = 0;
	rotate_shift = 1;
	ariphmethic_shift = 0;
		for (cnt = 5'd0; cnt < 5'd8; cnt = cnt + 5'd1)
			#1 sl = cnt;
	
	/* ariphmetic shift test */
	#1 in = 32'b01111111111111110000000000000000; 
	sl = 5'b00000; 
	left_or_right = 1'b0; 
	logic_shift = 0;
	rotate_shift = 0;
	ariphmethic_shift = 1;
		for (cnt = 5'd0; cnt < 5'd8; cnt = cnt + 5'd1)
			#1 sl = cnt;
			
	#1 in = 32'b11111111111111110000000000000000; 
	sl = 5'b00000; 
	left_or_right = 1'b1; 
	logic_shift = 0;
	rotate_shift = 0;
	ariphmethic_shift = 1;
		for (cnt = 5'd0; cnt < 5'd8; cnt = cnt + 5'd1)
			#1 sl = cnt;
	
	
end

initial
	#57 $finish;

	initial begin
	// Initialize Inputs
	in = 0;
	sl = 0;
	left_or_right = 0;
	logic_shift = 0;
	rotate_shift = 0;
	ariphmethic_shift = 0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule

