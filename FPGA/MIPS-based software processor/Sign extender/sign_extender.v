/* 
 * Implementation of sign extender.
 */


module sign_extender (in, out);

parameter in_bits  = 16;
parameter out_bits = 32;

input [in_bits-1 : 0] in;
output reg [out_bits-1 : 0] out;

/* 
 * @* means that changing of any signal, which is inside the "always" block,
 * leads to repeat the "always" block.
 * This way we can implement combinational logick.
 */
always @*
begin
	out = {out_bits{in[in_bits-1]}};
	out[in_bits-1 : 0] = in;
end

endmodule
