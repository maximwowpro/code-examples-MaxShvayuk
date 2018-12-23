module logic_unit (
	input logic [31:0] a, 
	input logic [31:0] b, 
	input logic [1:0] mode, 
	
	output logic [31:0] y
	);


always @*
begin
case(mode)
	2'b00: y=a&b;		
	2'b01 : y=a|b;	
	2'b10 : y=~(a|b);		
	2'b11 : y=a^b; 
endcase
end
endmodule