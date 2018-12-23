module register_file_mips (clk, r_1_en, addr_r_1, r_data_1, 
				r_2_en, addr_r_2, r_data_2, 
				w_en, addr_w, w_data, 
				arst, test0, test1, test2, test3, test4, test5, test6, 
				test7, test8, test9, test10, test11, test12, test13, test14, 
				test15, test16, test17, test18, test19, test20, test21, test22,
				test23, test24, test25, test26, test27, test28, test29, test30, test31 );

parameter n_bit  = 31;		//how many bit are there in one register
parameter n_reg  = 5 ;		//how many bits we should to adress all registers

input clk, arst;

input  r_1_en;			//"1" - read from channel 1 enable, "0" - disable
input  [n_reg : 0] addr_r_1;	//number of register (0 - 31) to read data to channel 1
output wire [n_bit : 0] r_data_1;	//bus for transmiting channel 1 read data

input  r_2_en;			//"1" - read from channel 2 enable, "0" - disable
input  [n_reg : 0] addr_r_2;	//number of register (0 - 31) to read data to channel 2
output wire [n_bit : 0] r_data_2;	//bus for transmiting channel 2 read data

input  w_en;			//"1" - write enable, "0" - disable
input  [n_reg : 0] addr_w;		//number of register (0 - 31) to write data
input  [n_bit : 0] w_data;		//bus for transmiting write data

output wire [31:0]test0;
output wire [31:0]test1;
output wire [31:0]test2;
output wire [31:0]test3;
output wire [31:0]test4;
output wire [31:0]test5;
output wire [31:0]test6;
output wire [31:0]test7;
output wire [31:0]test8;
output wire [31:0]test9;
output wire [31:0]test10;
output wire [31:0]test11;
output wire [31:0]test12;
output wire [31:0]test13;
output wire [31:0]test14;
output wire [31:0]test15;
output wire [31:0]test16;
output wire [31:0]test17;
output wire [31:0]test18;
output wire [31:0]test19;
output wire [31:0]test20;
output wire [31:0]test21;
output wire [31:0]test22;
output wire [31:0]test23;
output wire [31:0]test24;
output wire [31:0]test25;
output wire [31:0]test26;
output wire [31:0]test27;
output wire [31:0]test28;
output wire [31:0]test29;
output wire [31:0]test30;
output wire [31:0]test31;


reg [n_bit : 0] matrix [n_bit : 0];

reg [n_bit : 0] r_data_1_reg;
reg [n_bit : 0] r_data_2_reg;

assign test0 = matrix[0];
assign test1 = matrix[1];
assign test2 = matrix[2];
assign test3 = matrix[3];
assign test4 = matrix[4];
assign test5 = matrix[5];
assign test6 = matrix[6];
assign test7 = matrix[7];
assign test8 = matrix[8];
assign test9 = matrix[9];
assign test10 = matrix[10];
assign test11 = matrix[11];
assign test12 = matrix[12];
assign test13 = matrix[13];
assign test14 = matrix[14];
assign test15 = matrix[15];
assign test16 = matrix[16];
assign test17 = matrix[17];
assign test18 = matrix[18];
assign test19 = matrix[19];
assign test20 = matrix[20];
assign test21 = matrix[21];
assign test22 = matrix[22];
assign test23 = matrix[23];
assign test24 = matrix[24];
assign test25 = matrix[25];
assign test26 = matrix[26];
assign test27 = matrix[27];
assign test28 = matrix[28];
assign test29 = matrix[29];
assign test30 = matrix[30];
assign test31 = matrix[31];




assign r_data_1 = r_data_1_reg;
assign r_data_2 = r_data_2_reg;

always @(posedge clk or posedge arst)
begin
	if (arst) begin
		//matrix <= 32'd0;
	end else begin
	if (1 === r_1_en)
		r_data_1_reg <= matrix[addr_r_1];
	else
		r_data_1_reg <= 32'd0;
	
	if (1 === r_2_en)
		r_data_2_reg <= matrix[addr_r_2];
	else
		r_data_2_reg <= 32'd0;
	
	if (1 === w_en)
		matrix[addr_w] <= w_data;
	end
end

endmodule
