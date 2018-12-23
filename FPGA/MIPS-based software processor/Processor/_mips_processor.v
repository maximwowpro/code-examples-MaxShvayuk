module processor_mips ( i_clk, i_reset );

input i_clk;
input i_reset;

wire [31:0] instruction;
wire [5:0] op_code;

wire is_jump;
wire r_1_en, r_2_en, w_en;
wire reg_dst;
wire alu_src;
wire is_branch;
wire mem_write;
wire mem_to_reg;
wire is_signed;

wire [1:0] alu_op_code;
wire [5:0] alu_funct;
wire [1:0] alu_op_type_1;
wire [1:0] alu_op_type_2;
wire alu_op_type_3;
wire alu_is_signed;
wire [5:0] alu_control_for_data_tract;

assign op_code   = instruction[31:26];
assign alu_funct = instruction[5 : 0];
assign alu_control_for_data_tract = {alu_op_type_1, alu_op_type_2, alu_op_type_3, alu_is_signed};

control_unit_main_mips 	   control_unit_main  ( .i_op_code(op_code), 
						.o_is_jump(is_jump), 
						.o_r_1_en(r_1_en), .o_r_2_en(r_2_en), .o_w_en(w_en),
						.o_reg_dst(reg_dst),
						.o_alu_src(alu_src),
						.o_alu_op_code(alu_op_code),
						.o_is_branch(is_branch),
						.o_mem_write(mem_write),
						.o_mem_to_reg(mem_to_reg),
						.o_is_signed(is_signed) );


control_unit_alu_mips	   control_unit_alu   ( .i_alu_op_code(alu_op_code),
						.i_alu_is_signed(is_signed),
						.i_funct(alu_funct),
						.o_op_type_1(alu_op_type_1),
						.o_op_type_2(alu_op_type_2),
						.o_op_type_3(alu_op_type_3),
						.o_is_signed(alu_is_signed) );


data_tract_mips data_tract    ( .in_clk(i_clk), /* in_instruction,*/ 
				.out_instruction(instruction),
				.in_is_jump(is_jump), 
				.in_r_1_en(r_1_en), 
				.in_r_2_en(r_2_en), 
				.in_w_en(w_en),
				.in_reg_dst(reg_dst),
				.in_alu_src(alu_src), 
				.in_is_branch(is_branch), 
				.in_mem_write(mem_write), 
				.in_mem_to_reg(mem_to_reg), 
				.in_alu_control(alu_control_for_data_tract), 
				.in_reset(i_reset) );



always @( posedge i_clk) begin
//	if (i_reset)
end








reg [5:0] alu_control_reg;


assign o_op_type_1 = alu_control_reg[5:4];
assign o_op_type_2 = alu_control_reg[3:2];
assign o_op_type_3 = alu_control_reg[1];
assign o_is_signed = alu_is_signed;


always @* begin
	case (alu_op_code)
		2'b00: begin	/* Adder */
			alu_control_reg = 6'b10_00_00;
		end
		
		2'b01: begin	/* Subtractor */
			alu_control_reg = 6'b10_01_00;
		end
		
		2'b10: begin	/* ALU behaviour defines by "funct" field */
			case (alu_funct)
				6'h0 : alu_control_reg = 6'b00_00_00;	/* sll */
				6'h2 : alu_control_reg = 6'b00_00_10;	/* srl */
				6'h3 : alu_control_reg = 6'b00_10_10;	/* sra */
				6'h20: alu_control_reg = 6'b10_00_00;	/* add */
				6'h22: alu_control_reg = 6'b10_01_00;	/* sub */
				6'h24: alu_control_reg = 6'b11_00_00;	/* AND */
				6'h25: alu_control_reg = 6'b11_01_00;	/* OR  */
				6'h26: alu_control_reg = 6'b11_11_00;	/* XOR */
				6'h27: alu_control_reg = 6'b11_10_00;	/* NOR */
			endcase
		end
		
		2'b11: begin	/* forbidden value - I set it as Adder */
			alu_control_reg = 6'b10_00_00;
		end
	endcase
	
	
end

endmodule















