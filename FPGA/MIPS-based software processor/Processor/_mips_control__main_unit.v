module control_unit_main_mips (i_op_code, 
				  o_is_jump, 
				  o_r_1_en, o_r_2_en, o_w_en,
				  o_reg_dst,
				  o_alu_src,
				  o_alu_op_code,
				  o_is_branch,
				  o_mem_write,
				  o_mem_to_reg,
				  o_is_signed,
				  o_alu_is_signed );

input [5:0] i_op_code;		/* op-code of instruction */

output reg o_is_jump;

output reg o_r_1_en, o_r_2_en, o_w_en;

output reg o_reg_dst;

output reg o_alu_src;

output wire [1:0] o_alu_op_code; /* control signals for ALU */

output reg o_alu_is_signed;		 /* control signal for ALU which defines operands are signed or unsigned */

output reg o_is_branch;

output reg o_mem_write;

output reg o_mem_to_reg;

output reg o_is_signed;

reg [1:0] alu_op_code_reg;


assign o_alu_op_code = alu_op_code_reg;


always @* begin
	case (i_op_code)
		6'd0: begin	/* R-type instruction */
			o_is_jump    = 0;
			o_r_1_en     = 1;
			o_r_2_en     = 1;
			o_w_en       = 1;
			o_reg_dst    = 1;
			o_alu_src    = 0;
			o_is_branch  = 0;
			o_mem_write  = 0;
			o_mem_to_reg = 0;
			alu_op_code_reg = 2'b10; /* ALU behaviour defines by "funct" field */
		end
		
		6'b100011: begin	/* lw - load word instruction */
			o_is_jump    = 0;
			o_r_1_en     = 1;
			o_r_2_en     = 0;
			o_w_en       = 1;
			o_reg_dst    = 0;
			o_alu_src    = 1;
			o_is_branch  = 0;
			o_mem_write  = 0;
			o_mem_to_reg = 1;
			alu_op_code_reg = 2'b00; /* ALU works as Adder */
		end
		
		6'b101011: begin	/* sw - store word instruction */
			o_is_jump    = 0;
			o_r_1_en     = 1;
			o_r_2_en     = 1;
			o_w_en       = 0;
			o_reg_dst    = 0;
			o_alu_src    = 1;
			o_is_branch  = 0;
			o_mem_write  = 1;
			o_mem_to_reg = 1;
			alu_op_code_reg = 2'b00; /* ALU works as Adder */
		end
		
		6'b000100: begin	/* beq - branch if equal instruction */
			o_is_jump    = 0;
			o_r_1_en     = 1;
			o_r_2_en     = 1;
			o_w_en       = 0;
			o_reg_dst    = 0;
			o_alu_src    = 0;
			o_is_branch  = 1;
			o_mem_write  = 0;
			o_mem_to_reg = 0;
			alu_op_code_reg = 2'b01; /* ALU works as Subtractor */
		end
		
		6'b000010: begin	/* j - unconditional jump instruction */
			o_is_jump    = 1;
			o_r_1_en     = 0;
			o_r_2_en     = 0;
			o_w_en       = 0;
			o_reg_dst    = 0;
			o_alu_src    = 0;
			o_is_branch  = 0;
			o_mem_write  = 0;
			o_mem_to_reg = 0;
			alu_op_code_reg = 2'b00; /* we dont need ALU, so it can work anyhow */
		end
		
		default: begin
			o_is_jump    = 0;
			o_r_1_en     = 0;
			o_r_2_en     = 0;
			o_w_en       = 0;
			o_reg_dst    = 0;
			o_alu_src    = 0;
			o_is_branch  = 0;
			o_mem_write  = 0;
			o_mem_to_reg = 0;
			alu_op_code_reg = 2'b00; /* ALU works as Subtractor */
		end
		
	endcase
	
	
end

endmodule















