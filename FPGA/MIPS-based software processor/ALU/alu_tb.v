`timescale 1ns / 1ps

module alu_tb ();

reg [1 : 0] in_op_type_1;

reg [1 : 0] in_op_type_2;

reg in_op_type_3;

reg is_signed;
reg [31 : 0] in_1;
reg [31 : 0] in_2;

wire [31:0] out_result;
wire out_slt;

//program_counter_mips program_counter_mips_obj (.clk(clk), .instruction(instruction), .is_jump(is_jump), .ptr(ptr), .reset(reset));

alu_mips alu_mips_obj (in_op_type_1, in_op_type_2, in_op_type_3, is_signed, in_1, in_2, out_result, out_slt);

initial
begin
	//logic test
	#1 in_op_type_1 = 2'b11;
	in_op_type_2 = 2'b00;	//AND
	in_1 = 32'd255;
	in_2 = 32'd143;
	
	#1 in_op_type_1 = 2'b11;
	in_op_type_2 = 2'b01;	//OR
	in_1 = 32'd255;
	in_2 = 32'd143;
	
	#1 in_op_type_1 = 2'b11;
	in_op_type_2 = 2'b10;	//NOR
	in_1 = 32'd255;
	in_2 = 32'd143;
	
	#1 in_op_type_1 = 2'b11;
	in_op_type_2 = 2'b11;	//XOR
	in_1 = 32'd255;
	in_2 = 32'd143;
	
	
	//arithm test UNSIGNED
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b00;	//ADD without owerflow
	is_signed = 0;
	in_1 = 32'd13;
	in_2 = 32'd19;
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b00;	//ADD WITH owerflow
	in_1 = 32'd3000000000;
	in_2 = 32'd4000000000;
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;	//sub without owerflow
	in_1 = 32'd50;
	in_2 = 32'd25;
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;	//sub WITH owerflow
	in_1 = 32'd25;
	in_2 = 32'd50;
	
	
	
	//arithm test SIGNED
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b00;	//ADD without owerflow
	is_signed = 1;
	in_1 = 32'd13;
	in_2 = 32'd19;
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b00;			        /* ADD WITH owerflow CASE 1 */
	in_1 = 32'd2000000000;
	in_2 = 32'd2000000000;

	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;			        /* sub with owerflow CASE 2 */
	in_1 = 32'd2000000000;
	in_2 = 32'b11_0001000110_0101001101_1000000000; /* -1 billion 		    */
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b00;			        /* ADD WITH owerflow CASE 3 */
	in_1 = 32'b10_0010001100_1010011011_0000000000; /* -2 billions		    */
	in_2 = 32'b10_0010001100_1010011011_0000000000; /* -2 billions		    */
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;				/* sub with owerflow CASE 4 */
	in_1 = 32'b10_0010001100_1010011011_0000000000; /* -2 billions		    */
	in_2 = 32'd2000000000;
	
	
	//in_1 = 32'b11_1111111111_1111111111_1111111011; /* -5		*/
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;	//sub without owerflow
	in_1 = 32'd50;
	in_2 = 32'd25;
	
	#1 in_op_type_1 = 2'b10;
	in_op_type_2 = 2'b01;	//sub without owerflow
	in_1 = 32'd25;
	in_2 = 32'd50;
	
	
	
	
	
	// SLT test
	#1 in_op_type_1 = 2'b01; //SLT out = 0
	in_1 = 32'd25;
	in_2 = 32'd50;
	
	#1 in_op_type_1 = 2'b01; //SLT out = 1
	in_1 = 32'd50;
	in_2 = 32'd25;
	
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b00;	// logic 
	in_op_type_3 = 0;	// left
	in_1 = 32'b1111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b00;	// logic 
	in_op_type_3 = 1;	// right
	in_1 = 32'b1111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b01;	// rotate
	in_op_type_3 = 0;	// left
	in_1 = 32'b1111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b01;	// rotate
	in_op_type_3 = 1;	// right
	in_1 = 32'b1111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b10;	// arithm
	in_op_type_3 = 0;	// left
	in_1 = 32'b0111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
	// shift test
	#1 in_op_type_1 = 2'b00; 
	in_op_type_2 = 2'b10;	// arithm
	in_op_type_3 = 1;	// right
	in_1 = 32'b1111100000_0000000000_000001111100;
	in_2 = 32'd0;
	#1in_2 = 32'd1;
	#1in_2 = 32'd2;
	#1in_2 = 32'd3;
	#1in_2 = 32'd4;
	#1in_2 = 32'd5;
	
end

initial
	#48 $finish;

	initial begin
	// Initialize Inputs

	in_op_type_1 = 0;
	in_op_type_2 = 0;
	in_op_type_3 = 0;
	is_signed = 0;
	in_1 = 0;
	in_2 = 0;
// 	out_result = 0;
// 	out_slt = 0;
	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
