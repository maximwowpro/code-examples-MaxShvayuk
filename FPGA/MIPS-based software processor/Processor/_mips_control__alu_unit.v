module control_unit_alu_mips  ( i_alu_op_code,
				i_alu_is_signed,
				i_funct,
				o_op_type_1,
				o_op_type_2,
				o_op_type_3,
				o_is_signed );

input  [1:0] i_alu_op_code;	/* ALU op-code */

input  i_alu_is_signed;

input  [5:0] i_funct;

output [1:0] o_op_type_1;

output [1:0] o_op_type_2;

output o_op_type_3;

output o_is_signed;


reg [5:0] alu_control_reg;


assign o_op_type_1 = alu_control_reg[5:4];
assign o_op_type_2 = alu_control_reg[3:2];
assign o_op_type_3 = alu_control_reg[1];
assign o_is_signed = i_alu_is_signed;


always @* begin
	case (i_alu_op_code)
		2'b00: begin	/* Adder */
			alu_control_reg = 6'b10_00_00;
		end
		
		2'b01: begin	/* Subtractor */
			alu_control_reg = 6'b10_01_00;
		end
		
		2'b10: begin	/* ALU behaviour defines by "funct" field */
			case (i_funct)
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















