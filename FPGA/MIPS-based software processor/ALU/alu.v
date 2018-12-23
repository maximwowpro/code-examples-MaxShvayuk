module alu_mips (in_op_type_1, in_op_type_2, in_op_type_3, is_signed, in_1, in_2, out_result, out_slt);

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

input is_signed;		/* determine are in_1 and in_2 signed or unsigned numbers. 1 for signed, 0 for unsigned */

output reg [31:0] out_result;
output reg out_slt;		/* for SLT operation: in_1 < in_2 = 1, in_1 > in_2 = 0. Also marks overflow. 1 - is overflow. 0 - in NOT overflow */

reg msb_overflow_check;		/* I use this as 33 bit of out_result		      */
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
				{msb_overflow_check, out_result} = in_1 + in_2;
			end
			2'b01: begin
				{msb_overflow_check, out_result} = in_1 - in_2;
			end
			endcase
			
			out_slt = (~is_signed & msb_overflow_check) | 							/* check for unsigned numbers 	*/
				  ( is_signed & ( (~in_1[31] & ~in_2[31] &  out_result[31] & ~in_op_type_2[0]) |	/* A+  ADD   B+  OUT-	 	*/
						  (~in_1[31] &  in_2[31] &  out_result[31] &  in_op_type_2[0]) |	/* A+  SUB   B-  OUT-	 	*/
						  ( in_1[31] &  in_2[31] & ~out_result[31] & ~in_op_type_2[0]) |	/* A-  ADD   B-  OUT+	 	*/
						  ( in_1[31] & ~in_2[31] & ~out_result[31] &  in_op_type_2[0]) ) );	/* A-  SUB   B+  OUT+	 	*/
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
