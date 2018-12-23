module instruction_memory_mips (in_addr, out_instruction);

parameter n_bit  = 31;
parameter memory_size  = 2047;

input [n_bit : 0] in_addr;

output wire [n_bit : 0] out_instruction;

reg [n_bit : 0] matrix [memory_size : 0];

initial $readmemh ( "mips_hex_program.hex" , matrix);

assign out_instruction = matrix[in_addr];


// initial
// begin
// 	matrix[1] = 32'haaaa;
// 
// 	matrix[2] = 32'hbbbb;
// 
// 	matrix[3] = 32'hcccc;
// 
// end

endmodule

