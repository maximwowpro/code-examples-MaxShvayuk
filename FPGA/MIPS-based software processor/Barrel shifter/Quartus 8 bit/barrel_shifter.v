/* 
 * I use a materials, writen by Dhaval Kaneria.
 * http://kaneriadhaval.blogspot.com/
 */


module barrel_shifter (SW, LEDR);

input  [12:0] SW;
output [7:0]  LEDR;

parameter n=7;

wire [n:0] in = SW[7:0];
wire [2:0] sh = SW[10:8];
wire shift_LeftRight  = SW[11];
wire rotate_LeftRight = SW[12];
reg  [n:0] out;

assign LEDR = out;

/* 
 * @* means that changing of any signal, which is inside the "always" block 
 * leads to repeat the "always" block 
 */
always @*
begin
	if (~shift_LeftRight)
		out=in<<sh;		/* simple logic shift left  */
	else if (shift_LeftRight)
		out = in>>sh;		/* simple logic shift right */
	else
		begin
			case(sh)	/* cyclic shift 	    */
				5'b001:
				out= (~rotate_LeftRight) ? {in[n-1:0],in[n]}:{in[0],in[n:1]};
				5'b010:
				out= (~rotate_LeftRight) ? {in[n-2:0],in[n:n-1]}:{in[1:0],in[n:2]};
				5'b011:
				out= (~rotate_LeftRight) ? {in[n-3:0],in[n:n-2]}:{in[2:0],in[n:3]};
				5'b100:
				out= (~rotate_LeftRight) ? {in[n-4:0],in[n:n-3]}:{in[3:0],in[n:4]};
				5'b101:
				out= (~rotate_LeftRight) ? {in[n-5:0],in[n:n-4]}:{in[4:0],in[n:5]};
				5'b110:
				out= (~rotate_LeftRight) ? {in[n-6:0],in[n:n-5]}:{in[5:0],in[n:6]};
				5'b111:
				out= (~rotate_LeftRight) ? {in[n-7:0],in[n:n-6]}:{in[6:0],in[n:7]};
				
				default:
				out=in;
			endcase
		end
	
end
endmodule
