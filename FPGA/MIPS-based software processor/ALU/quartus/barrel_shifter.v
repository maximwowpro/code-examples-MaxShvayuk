/* 
 * Implementation of 32-bits barrel shifter.
 *
 * I used a materials, writen by Dhaval Kaneria.
 * http://kaneriadhaval.blogspot.com/
 */


module barrel_shifter (in, sl, left_of_right, logick_rotate_ariphmetic_shift, out);

parameter n = 31;

input [n : 0] in;
input [4 : 0] sl;				/* means "shift lenght"	    */
input left_of_right;				/* left == 0 , right == 1   */
input [1 : 0] logick_rotate_ariphmetic_shift;	/* logih shift == 00, rotate shift == 01, ariphmetic shift == 10*/

output reg [n : 0] out;

reg  [4 : 0] cnt_;				/* counter of for-loop	    */


/* 
 * @* means that changing of any signal, which is inside the "always" block,
 * leads to repeat the "always" block.
 * This way we can implement combinational logick.
 */
always @*
begin
	case (logick_rotate_ariphmetic_shift)
		2'b00:
			out = (~left_of_right) ? in << sl : in >> sl ;
		
		2'b01:	begin
			out = in;
			/* rotate shift left or right */
			for (cnt_ = 5'd0; cnt_ < 5'd31; cnt_ = cnt_ + 5'd1)
			begin
				if (cnt_ <= sl && sl != 5'd0) begin
					out = (~left_of_right) ? { out[n-1 : 0], out[n] } : { out[0], out[n : 1] };
				end
				
			end
		end
		
		2'b10:  begin
			out = (~left_of_right) ? in << sl : in[n-1 : 0] >> sl ;
			out[n] = in[n];
		end
		
	endcase


// // // 	/* === is case(value) equality operator */
// // // 	if (2'b00 === logick_rotate_ariphmetic_shift && 1'b0 === left_of_right)
// // // 		/* logic shift left  */
// // // 		out = in << sl;
// // // 	
// // // 	else if (2'b00 === logick_rotate_ariphmetic_shift && 1'b1 === left_of_right)
// // // 		/* logic shift right */
// // // 		out = in >> sl;
// // // 	
// // // 	else if (2'b01 === logick_rotate_ariphmetic_shift)
// // // 	begin
// // // 		out = in;
// // // 		/* rotate shift left or right */
// // //  		for (cnt_ = 5'd0; cnt_ < 5'd31; cnt_ = cnt_ + 5'd1)
// // //  		begin
// // //  			if (cnt_ <= sl && sl != 5'd0) begin
// // // 				out = (~left_of_right) ? { out[n-1 : 0], out[n] } : { out[0], out[n : 1] };
// // // 			end
// // // 			
// // // 		end
// // // 	end
// // // 	
// // // 	else 
// // // 	begin
// // // 		/* ariphmetic shift left or right */
// // // 		out = (~left_of_right) ? in << sl : in[n-1 : 0] >> sl ;
// // // 		out[n] = in[n];
// // // 	end
end

endmodule
