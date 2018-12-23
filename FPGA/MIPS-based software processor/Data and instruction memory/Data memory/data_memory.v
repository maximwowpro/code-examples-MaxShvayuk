module data_memory_mips (in_clk, in_we, in_addr, in_write_data, out_read_data);

parameter n_bit  = 31;
parameter memory_size = 2047;

input in_clk, in_we;			// in_we - write enable to memory

input [n_bit : 0] in_addr;

input [n_bit : 0] in_write_data;

output wire [n_bit : 0] out_read_data;

reg [n_bit : 0] matrix [memory_size : 0];

assign out_read_data = matrix[in_addr];

always @(posedge in_clk)
begin
	if (in_we)
		matrix[in_addr] <= in_write_data;
end

endmodule
