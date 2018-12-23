module gpio_one_port (i_clk, i_enable, i_data_dir, i_data_transmit, o_data_received, io_pin_states);

parameter N = 15;			/* determines number of bits in one GPIO port 		*/

input               i_clk;		/* clock signal 					*/
input               i_enable;		/* 1 == enable, 0 == disable				*/
input       [N : 0] i_data_dir; 	/* set direction of the bits of GPIO port		*/
input       [N : 0] i_data_transmit; 	/* data, to transmit from GPIO port (data OUT)  	*/
inout wire  [N : 0] io_pin_states; 	/* logic states which presents at pins of GPIO port 	*/

output      [N : 0] o_data_received; 	/* data, received from GPIO port    (data IN)		*/


gpio_one_pin gpio_pins_obj [N : 0] (.i_clk           (i_clk)           ,
				    .i_enable	     (i_enable)	       ,
				    .i_data_dir      (i_data_dir)      , 
				    .i_data_transmit (i_data_transmit) , 
				    .o_data_received (o_data_received) ,
				    .io_pin_state    (io_pin_states)   );

endmodule
