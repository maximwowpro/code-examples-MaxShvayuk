module alu
(
input logic [1:0] alu_slct,
input logic [1:0] shft_op,
input logic  arhmt_op, sign_ctrl,
input logic [1:0] logic_op,
input logic [31:0] a,
input logic [31:0] b,

output logic [31:0] alu_res,
output logic overflow, zero  
);

logic [31:0] logic_out;
logic [31:0] arhmt_out;
logic [31:0] shift_out;

logic arhmt_operation;

always @*
arhmt_operation=(alu_slct===2'b01)?1'b1:arhmt_op;

logic_unit logic_unit_inst(.a, .b, .mode(logic_op), .y(logic_out));
arithmetic_module arithmetic_module(.a, .b, .arithmetic_ctrl(arhmt_operation), .sign_ctrl, .overflow, .y(arhmt_out));
barrel_shifter(.numb(b), .shift(a[4:0]), .mode(shft_op), .out_numb(shift_out));

always @*
begin
case(alu_slct)
	2'b00: alu_res=shift_out;		
	2'b01: alu_res={30'b0, overflow!==arhmt_out[31]};
	2'b10: alu_res=arhmt_out;		
	2'b11: alu_res=logic_out; 
endcase
end

endmodule