module gpio_one_pin (i_clk, i_data_dir, i_data_transmit, o_data_received, io_pin_state);

input             i_clk;	/* clock signal 					*/
input  	     i_data_dir; 	/* set direction of the bit of GPIO pin			*/
input   i_data_transmit; 	/* data, to transmit from GPIO pin (data OUT)	  	*/

inout      io_pin_state; 	/* logic states which presents at GPIO pin 		*/

output   o_data_received; 	/* data, received from GPIO pin    (data IN)		*/

reg first, second;

tri_buf tri_bufs_obj (.i_in(first), .o_out(io_pin_state), .i_enable(i_data_dir));

assign o_data_received = second;

always @(posedge i_clk)
begin	
	second <= io_pin_state;
	first  <= i_data_transmit;
end

endmodule




module gpio_one_port (i_clk, i_data_dir, i_data_transmit, o_data_received, io_pin_state);

parameter N = 15;

input               i_clk;		/* clock signal 					*/
input       [N : 0] i_data_dir; 	/* set direction of the bits of GPIO port		*/
input       [N : 0] i_data_transmit; 	/* data, to transmit from GPIO port (data OUT)  	*/
inout wire  [N : 0] io_pin_states; 	/* logic states which presents at pins of GPIO port 	*/

output      [N : 0] o_data_received; 	/* data, received from GPIO port    (data IN)		*/


gpio_one_pin [N : 0] gpio_pins_obj (.i_clk           (i_clk)           , 
				    .i_data_dir      (i_data_dir)      , 
				    .i_data_transmit (i_data_transmit) , 
				    .o_data_received (o_data_received) ,
				    .io_pin_state    (io_pin_states)   );

endmodule
