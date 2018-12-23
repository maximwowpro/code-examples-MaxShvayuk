module data_tract_mips (in_clk,
			out_instruction,
			in_is_jump, 
			in_r_1_en, in_r_2_en, in_w_en,
			in_reg_dst, in_alu_src, in_is_branch, in_mem_write, 
			in_mem_to_reg, in_alu_control, in_reset);


input in_clk;				

//input [31 : 0] in_instruction;

output wire [31:0] out_instruction;

input in_is_jump;			/* control signal for jump instruction 				*/

input in_r_1_en, in_r_2_en, in_w_en;	/* control signals for register file 				*/

input in_reg_dst;			/* control signal for mux which determines addr_write in register file */

input in_alu_src; 			/* control signal for ALU in_2 source mux 			*/

input in_is_branch;			/* control signal for "beq" instruction 			*/

input in_mem_write;			/* control signal for data memory read/write mode 		*/

input in_mem_to_reg;			/* determines what data should be written to the register file 	*/

input [5 : 0] in_alu_control;		/* control signals for ALU 					*/

input in_reset;				/* reset signal for program counter				*/


reg [31 : 0] instruction_start;		/* start point for program counter 				*/

wire [31 : 0] current_instruction_addr;	/* connect it to program counter's output 			*/
wire [31 : 0] current_instruction;	/* connect it to instruction memory output 			*/

wire [31 : 0] r_f_read_data_1;		/* Register File "Read data 1" output				*/
wire [31 : 0] r_f_read_data_2;		/* Register File "Read data 2" output				*/
wire [31 : 0] r_f_write_data;		/* Register File "Write data"  input				*/
wire [ 4 : 0] r_f_write_addr;		/* Register File "address write"  input				*/

wire [31 : 0] extended_immediate;	/* Sign Extender output						*/

wire [31 : 0] alu_2_operand;	/* ALU's in_2 input						*/
wire [31 : 0] alu_result;		/* ALU's result							*/
wire 	      alu_slt;

wire [31 : 0] data_memory_out_val;	/* Data Memory's output (result of reading from Data Memory)	*/


/* wires for jump instruction implementation */
wire [25:0] jump_label_before_shift;
wire [27:0] addr_jump_2_part;
wire [31:28] addr_jump_1_part;
wire [31:0] addr_jump_full;

assign jump_label_before_shift = current_instruction[25:0];
assign addr_jump_2_part = jump_label_before_shift << 2;
assign addr_jump_1_part = curr_instruction_addr_plus_4[31:28];
assign addr_jump_full = {addr_jump_1_part, addr_jump_2_part};

mux_32_bit mux_is_branch (


assign out_instruction = current_instruction;


/* determine all processor's elements */
program_counter_mips program_counter (in_clk, instruction_start, in_is_jump, current_instruction_addr, in_reset);

instruction_memory_mips instruction_memory (current_instruction_addr, current_instruction);

register_file_mips register_file (in_clk, 
				  in_r_1_en, current_instruction[25 : 21], r_f_read_data_1,
				  in_r_2_en, current_instruction[20 : 16], r_f_read_data_2,
				  in_w_en  , r_f_write_addr, r_f_write_data);
				  
sign_extender_mips sign_extender (current_instruction[15 : 0], extended_immediate);

alu_mips alu (in_alu_control[5:4], in_alu_control[3:2], in_alu_control[1], in_alu_control[0],
	      r_f_read_data_1, alu_2_operand, alu_result, alu_slt);

data_memory_mips data_memory (in_clk, in_mem_write, alu_result, r_f_read_data_2, data_memory_out_val);


/* determine all processor's multiplexers to connect the elements */
mux_5_bit mux_reg_dst (in_reg_dst, current_instruction[20:16], current_instruction[15:11], r_f_write_addr);

mux_32_bit mux_alu_src (in_alu_src, r_f_read_data_2, extended_immediate, alu_2_operand);

mux_32_bit mux_mem_to_reg (in_mem_to_reg, alu_result, data_memory_out_val, r_f_write_data);

always @(posedge in_clk) 
begin
	
	
	
	
end

endmodule
