module program_counter_mips(clk, instruction, is_jump, ptr, reset);

input clk ;
input reset;
input is_jump;			//should we execute "jump" instruction, or not?
input [31 : 0] instruction ;	//instruction

output reg [31:0] ptr;		//pointer to instruction adress in memory

always @(posedge clk )
begin
	if (reset)
		ptr = 32'd0;
	else if (is_jump)
		ptr[27 : 0] = (instruction[25:0] << 2);
	else 
		ptr = ptr + 32'd4;
end

endmodule
