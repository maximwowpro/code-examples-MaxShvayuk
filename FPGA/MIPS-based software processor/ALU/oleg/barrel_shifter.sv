module barrel_shifter (
	input logic [31:0] numb, 
	input logic [4:0] shift, 
	input logic [1:0] mode, 
	
	output logic [31:0] out_numb
	);

logic [31:0] l_shifted;
logic [63:0] r_shifted;
logic [31:0] a_r_shifted;

assign l_shifted = numb << shift;
assign r_shifted = {numb, numb} >> shift;
assign a_r_shifted = numb >>> shift;

always @*
begin
case(mode)
	2'b00: out_numb=l_shifted;		//sll
	2'b01: out_numb=r_shifted[63:32];	//srl
	2'b10: out_numb=a_r_shifted;		//sra
	2'b11: out_numb=r_shifted[31:0];       //ror (mb rotate operation right)
endcase
end
endmodule