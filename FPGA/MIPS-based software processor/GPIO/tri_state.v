module tri_buf (i_in, o_out, i_enable);

input  i_in;
input  i_enable;
inout wire o_out;

assign o_out = (i_enable) ? i_in : 1'bz;
 
// always @* begin
// 	o_out = (i_enable) ? i_in : 1'bz;
// end

endmodule
