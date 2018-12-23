module program_counter_mips(clk, instruction, ptr;

input clk ;
input [31 : 0] instruction ;	//instruction

output [31 : 0] ptr;

reg [31:0] tmp_reg;		//pointer to instruction adress in memory

assign ptr = tmp_reg;

always @(posedge clk )
begin

	tmp_reg = instruction + 32'd4;
end

endmodule
