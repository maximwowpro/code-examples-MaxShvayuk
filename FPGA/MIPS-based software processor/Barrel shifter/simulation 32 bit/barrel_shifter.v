module barrel_shifter (in, sl, left_or_right, logic_shift, rotate_shift, ariphmethic_shift, out);

parameter n = 31;

input [n : 0] in;
input [4 : 0] sl;		/* means "shift lenght"	    		*/
input left_or_right;		/* left == 0 , right == 1   		*/
input logic_shift;		/* 1 to select one of kinds of shifts 	*/
input rotate_shift;
input ariphmethic_shift;

output reg [n : 0] out;

reg  [4 : 0] cnt;		/* counter of for-loop	    */


/* 
 * @* means that changing of any signal, which is inside the "always" block,
 * leads to repeat the "always" block.
 * This way we can implement combinational logick.
 */
always @*
begin
	case (left_or_right)
		1'b0: begin /* means shift left */
			if (1 === logic_shift || 1 === ariphmethic_shift) /* logic and ariphmethic shifts left are the same one */
				out = in << sl;
			else if (1 === rotate_shift) begin
				out = in;
				for (cnt = 5'd0; cnt < 5'd32; cnt = cnt + 5'd1) begin
					if (cnt <= sl)
						out = { out[n-1 : 0], out[n] };
				end
			end
 		end
		
		1'b1: begin /* means shift right */
			if (1 === logic_shift)
				out = in >> sl;
			else if (1 === rotate_shift) begin
				out = in;
				for (cnt = 5'd0; cnt < 5'd32; cnt = cnt + 5'd1) begin
					if (cnt <= sl)
						out = { out[0], out[n : 1] };
				end
			end
			else if (1 === ariphmethic_shift)
				out = in[n-1 : 0] >> sl;
 		end
	endcase


	
// // 	/* === is case(value) equality operator */
// // 	if (2'b00 === logick_rotate_ariphmetic_shift && 1'b0 === left_of_right)
// // 		/* logic shift left  */
// // 		out = in << sl;
// // 	
// // 	else if (2'b00 === logick_rotate_ariphmetic_shift && 1'b1 === left_of_right)
// // 		/* logic shift right */
// // 		out = in >> sl;
// // 	
// // 	else if (2'b01 === logick_rotate_ariphmetic_shift)
// // 	begin
// // 		out = in;
// // 		/* rotate shift left or right */
// // 		for (cnt = 5'd0; cnt < 5'd32; cnt = cnt + 5'd1)
// // 		begin
// // 			if (cnt <= sl)
// // 				out = (~left_of_right) ? { out[n-1 : 0], out[n] } : { out[0], out[n : 1] };
// // 		end
// // 	end
// // 	
// // 	else 
// // 		/* ariphmetic shift left or right */
// // 		out = (~left_of_right) ? in << sl : in[n-1 : 0] >> sl;
end

endmodule

//asic-world чекнуть
