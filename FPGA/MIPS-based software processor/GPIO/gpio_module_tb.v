`timescale 1ns / 1ps

module gpio_module_tb#(parameter N = 15, parameter NUM_BITS_IN_PORT_SELECT = 3) ();

reg               i_clk;		/* clock signal 					*/
reg       [NUM_BITS_IN_PORT_SELECT : 0] i_port_select; /* selects one of 4 GPIO ports		*/
reg       [N : 0] i_data_dir; 		/* set direction of the bits of GPIO port		*/
reg       [N : 0] i_data_transmit; 	/* data, to transmit from GPIO port (data OUT)  	*/
reg       [N : 0] io_pin_states; 	/* logic states which presents at pins of GPIO port 	*/

wire      [N : 0] o_data_received; 	/* data, received from GPIO port    (data IN)		*/


wire [N : 0] io_pin_states_wire;
assign io_pin_states_wire = io_pin_states;


gpio_module gpio_module_obj    (.i_clk           (i_clk)           	,
				.i_port_select   (i_port_select)	,
				.i_data_dir      (i_data_dir)      	, 
				.i_data_transmit (i_data_transmit) 	, 
				.o_data_received (o_data_received) 	,
				.io_pin_states   (io_pin_states_wire)   );


initial
begin
// 	#1 i_clk = 1;
// 	i_data_dir      = 16'hFFFF;
// 	i_data_transmit = 16'hAAAA;
// 	io_pin_states   = 16'hFF00;
// 	#1 i_clk = 0;
// 	
// 	#1 i_clk = 1;
// 	i_data_dir      = 16'h00FF;
// 	i_data_transmit = 16'hAAAA;
// 	io_pin_states   = 16'hFF00;
// 	#1 i_clk = 0;
// 	
// 	#1 i_clk = 1;
// 	i_data_dir      = 16'h00FF;
// 	i_data_transmit = 16'h0000;
// 	io_pin_states   = 16'hFFFF;
// 	#1 i_clk = 0;

	#1 i_port_select = 4'b0001;
	i_clk = 1;
	i_data_dir      = 16'hFFFF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'hz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'b01110101zzzzzzzz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'h0000;
	io_pin_states   = 16'b11111111zzzzzzzz;
	#1 i_clk = 0;
	
	
	
	
	
	#1 i_port_select = 4'b0010;
	i_clk = 1;
	i_data_dir      = 16'hFFFF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'hz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'b01110101zzzzzzzz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'h0000;
	io_pin_states   = 16'b11111111zzzzzzzz;
	#1 i_clk = 0;
	
	
	
	
	#1 i_port_select = 4'b0100;
	i_clk = 1;
	i_data_dir      = 16'hFFFF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'hz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'b01110101zzzzzzzz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'h0000;
	io_pin_states   = 16'b11111111zzzzzzzz;
	#1 i_clk = 0;
	
	
	
	
	#1 i_port_select = 4'b1000;
	i_clk = 1;
	i_data_dir      = 16'hFFFF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'hz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'hAAAA;
	io_pin_states   = 16'b01110101zzzzzzzz;
	#1 i_clk = 0;
	
	#1 i_clk = 1;
	i_data_dir      = 16'h00FF;
	i_data_transmit = 16'h0000;
	io_pin_states   = 16'b11111111zzzzzzzz;
	#1 i_clk = 0;
	
	
end

initial
	#70 $finish;

	initial begin
	// Initialize Inputs

	i_clk = 0;
	i_data_dir      = 16'h0000;
	i_data_transmit = 16'h0000;
	io_pin_states   = 16'h0000;
//	o_data_received = 16'h0000;

	// Wait 100 ns for global reset to finish
	#100;

end

endmodule
