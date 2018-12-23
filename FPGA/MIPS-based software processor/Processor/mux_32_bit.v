module mux_32_bit (in_control, in_0, in_1, out_result);

parameter n_bit  = 32;

input in_control;

input [n_bit : 0] in_0;
input [n_bit : 0] in_1;

output wire [n_bit : 0] out_result;

assign out_result = (in_control ? in_1 : in_0);

endmodule
