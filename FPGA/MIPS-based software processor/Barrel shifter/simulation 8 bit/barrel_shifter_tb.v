`timescale 1ns / 1ps

module barrel_shifter_tb#(parameter n=7) ();

reg  [n : 0] in;
reg  [2 : 0] sh;
reg  shift_LeftRight, rotate_LeftRight;
wire [n : 0] out;

barrel_shifter shifter_obj(.in (in), .sh (sh), .shift_LeftRight (shift_LeftRight), .rotate_LeftRight (rotate_LeftRight), .out (out));

initial
begin
	#1 in=8'b11110000; sh=3'b000; rotate_LeftRight=1'b1; shift_LeftRight=1'bx;
		#1 sh=3'b001;
		#1 sh=3'b010;
		#1 sh=3'b011;
		#1 sh=3'b100;
		#1 sh=3'b101;
		#1 sh=3'b110;
		#1 sh=3'b111;
		
	#1 sh=3'b000; in=8'b11110000; rotate_LeftRight=1'b0;
		#1 sh=3'b001;
		#1 sh=3'b010;
		#1 sh=3'b011;
		#1 sh=3'b100;
		#1 sh=3'b101;
		#1 sh=3'b110;
		#1 sh=3'b111;

	#1 sh=3'b000; in=8'b11110000; rotate_LeftRight=1'bx; shift_LeftRight=1'b0;
		#1 sh=3'b001;
		#1 sh=3'b010;
		#1 sh=3'b011;
		#1 sh=3'b100;
		#1 sh=3'b101;
		#1 sh=3'b110;
		#1 sh=3'b111;

	#1 sh=3'b000; in=8'b11110000; shift_LeftRight=1'b1;
		#1 sh=3'b001;
		#1 sh=3'b010;
		#1 sh=3'b011;
		#1 sh=3'b100;
		#1 sh=3'b101;
		#1 sh=3'b110;
		#1 sh=3'b111;
		
end

initial
	#32 $finish;

	initial begin
	// Initialize Inputs
	in = 0;
	sh = 0;
	shift_LeftRight = 0;
	rotate_LeftRight = 0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
