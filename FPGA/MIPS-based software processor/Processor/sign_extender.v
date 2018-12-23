/* 
 * Implementation of sign extender.
 */


module sign_extender_mips (in, out);

parameter in_bits  = 15;
parameter out_bits = 31;

input [in_bits : 0] in;
output wire [out_bits : 0] out;


reg [out_bits : 0] out_reg;


assign out = out_reg;

/* 
 * @* means that changing of any signal, which is inside the "always" block,
 * leads to repeat the "always" block.
 * This way we can implement combinational logick.
 */
always @*
begin
	out_reg = {out_bits{in[in_bits]}};
	out_reg[in_bits : 0] = in;
end

endmodule
