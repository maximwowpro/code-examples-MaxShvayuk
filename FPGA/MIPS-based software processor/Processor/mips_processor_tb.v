`timescale 1ns / 1ps

module testbench;

parameter PERIOD = 2;

reg clk, reset;

processor_mips processor (clk, reset);

initial begin
    #1 
    clk = 0;
    reset = 1;
    #1
    clk = 1;
    #1
    clk = 0;
    reset = 0;
    
    forever #(PERIOD/2) clk = ~clk;
end

initial begin
	#10000
	$finish;
end

endmodule
