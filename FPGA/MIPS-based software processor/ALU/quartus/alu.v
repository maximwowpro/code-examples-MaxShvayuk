module alu_mips (in_op_type_1, in_op_type_2, in_op_type_3, in_1, in_2, out_result, out_slt);

/*
 * in_op_type_1:
 * operation's type selector №1. 
 * shift = 00 (in_1 - value to rotate, in_2 - on which num of bits should we rotate?)
 * SLT   = 01
 * arith = 10
 * logic = 11
 */
input [1 : 0] in_op_type_1;

/* 
 * in_op_type_2:
 * operation's type selector №2.
 * if in_op_type_1 = logic:
	AND = 00
	OR  = 01
	NOR = 10
	XOR = 11
   if in_op_type_1 = SLT
	do nothing
   if in_op_type_1 = arith
	ADD = 00
	SUB = 01 (in_1 - in_2)
   if in_op_type_1 = shift
	shift logic  = 00
	shift rotate = 01
	shift arithm = 10
 */
input [1 : 0] in_op_type_2;

input in_op_type_3;		/* determine left or right shift. 0 = left, 1 = right */

input [31 : 0] in_1;		/* input 1 */
input [31 : 0] in_2;		/* input 2 */

output reg [31:0] out_result;
output reg out_slt;		/* for SLT operation: in_1 < in_2 = 1, in_1 > in_2 = 0. Also marks overflow */

reg [32 : 0] tmp_res;
wire [31 : 0] tmp_shift_res;

barrel_shifter shifter_obj (in_1, in_2[4 : 0], in_op_type_3, in_op_type_2, tmp_shift_res);

always @*
begin
	out_slt = 0;

	case (in_op_type_1)
		2'b00: begin
			out_result = tmp_shift_res;
		end
		2'b01: begin
			if (in_1 < in_2) begin
				out_slt = 1;
				out_result = 32'd0;
			end
		end
		2'b10: begin
			case (in_op_type_2)
			2'b00: begin
				tmp_res = in_1 + in_2;
				out_result = tmp_res [31 : 0];
				if (tmp_res[32] === 1'b1)
					out_slt = 1;
			end
			2'b01: begin
				out_result = in_1 - in_2;
				if (out_result[31] === 1'b0 && in_1[31] === 1'b1 && in_2[31] === 1'b1)
					out_slt = 1;
			end
			endcase
		end
		2'b11: begin
			case (in_op_type_2)
				2'b00: begin
					out_result = in_1 & in_2;
				end
				2'b01: begin
					out_result = in_1 | in_2;
				end
				2'b10: begin
					out_result = ~(in_1 | in_2);
				end
				2'b11: begin
					out_result = in_1 ^ in_2;
				end
			endcase
		end
	endcase

end

endmodule
