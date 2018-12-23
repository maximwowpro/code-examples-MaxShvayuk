`timescale 1ns / 1ps

module register_file_tb#(parameter n_bit = 31, parameter n_reg = 5) ();

reg clk;

reg 	   r_1_en;			//"1" - read from channel 1 enable, "0" - disable
reg 	   [5  : 0] addr_r_1;	//number of register (0 - 31) to read data to channel 1
wire	   [31 : 0] r_data_1;	//bus for transmiting channel 1 read data

reg 	   r_2_en;			//"1" - read from channel 2 enable, "0" - disable
reg 	   [5  : 0] addr_r_2;	//number of register (0 - 31) to read data to channel 2
wire	   [31 : 0] r_data_2;	//bus for transmiting channel 2 read data

reg 	   w_en;			//"1" - write enable, "0" - disable
reg        [5  : 0] addr_w;		//number of register (0 - 31) to write data
reg        [31 : 0] w_data;		//bus for transmiting write data

// wire [31:0]test0;
// wire [31:0]test1;
// wire [31:0]test2;
// wire [31:0]test3;
// wire [31:0]test4;
// wire [31:0]test5;
// wire [31:0]test6;
// wire [31:0]test7;
// wire [31:0]test8;
// wire [31:0]test9;
// wire [31:0]test10;
// wire [31:0]test11;
// wire [31:0]test12;
// wire [31:0]test13;
// wire [31:0]test14;
// wire [31:0]test15;
// wire [31:0]test16;
// wire [31:0]test17;
// wire [31:0]test18;
// wire [31:0]test19;
// wire [31:0]test20;
// wire [31:0]test21;
// wire [31:0]test22;

// register_file_mips register_file_mips_obj (.clk(clk), 
// 					   .r_1_en(r_1_en), .addr_r_1(addr_r_1), .r_data_1(r_data_1),
// 					   .r_2_en(r_2_en), .addr_r_2(addr_r_2), .r_data_2(r_data_2),
// 					   .w_en(w_en), .addr_w(addr_w), .w_data(w_data),
// 					   .test0(test0),
// 					   .test1(test1),
// 					   .test2(test2),
// 					   .test3(test3),
// 					   .test4(test4),
// 					   .test5(test5),
// 					   .test6(test6),
// 					   .test7(test7),
// 					   .test8(test8),
// 					   .test9(test9),
// 					   .test10(test10),
// 					   .test11(test11),
// 					   .test12(test12),
// 					   .test13(test13),
// 					   .test14(test14),
// 					   .test15(test15),
// 					   .test16(test16),
// 					   .test17(test17),
// 					   .test18(test18),
// 					   .test19(test19),
// 					   .test20(test20),
// 					   .test21(test21),
// 					   .test22(test22) );


register_file_mips register_file_mips_obj (.clk(clk), 
					   .r_1_en(r_1_en), .addr_r_1(addr_r_1), .r_data_1(r_data_1),
					   .r_2_en(r_2_en), .addr_r_2(addr_r_2), .r_data_2(r_data_2),
					   .w_en(w_en), .addr_w(addr_w), .w_data(w_data) );
					   
initial
begin
	#1
	clk = 1;
	w_en = 1;
	addr_w = 32'd10;
	w_data = 32'hAAAA;
	
	#1
	clk = 0;
	
	#1
	clk = 1;
	w_en = 0;
	r_1_en = 1;
	addr_r_1 = 10;
	
	#1
	clk = 0;
	
	#1
	clk = 1;
	r_1_en = 0;
	r_2_en = 1;
	addr_r_2 = 10;
	
	#1
	clk = 0;
	

end

initial
	#100 $finish;

	initial begin
	// Initialize Inputs
	r_1_en   = 0;
	addr_r_1 = 0;

	r_2_en   = 0;
	addr_r_2 = 0;

	w_en   = 0;
	addr_w = 0;
	w_data = 0;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
