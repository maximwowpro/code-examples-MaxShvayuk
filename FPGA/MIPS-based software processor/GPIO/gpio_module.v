module gpio_module (i_clk, i_data_dir, i_data_transmit, o_data_received, io_pin_states, i_port_select);

parameter   N = 15;			/* determines number of bits in one GPIO port 		*/
parameter   NUM_PORTS = 3; 		/* determines the number of I/O ports in GPIO module 	*/
//parameter   NUM_BITS_IN_PORT_SELECT = 1;

input       [NUM_PORTS : 0] i_port_select; /* selects one of 4 GPIO ports			*/
input               i_clk;		/* clock signal 					*/
input       [N : 0] i_data_dir; 	/* set direction of the bits of GPIO port		*/
input       [N : 0] i_data_transmit; 	/* data, to transmit from GPIO port (data OUT)  	*/
inout wire  [N : 0] io_pin_states; 	/* logic states which presents at pins of GPIO port 	*/

output      [N : 0] o_data_received; 	/* data, received from GPIO port    (data IN)		*/

reg 	    [N : 0] data_transmit;
reg 	    [N : 0] data_receive;
reg 	    [N : 0] direction;


gpio_one_port gpio_ports_obj [NUM_PORTS : 0] 
				   (.i_clk           (i_clk)           , 
				    .i_enable        (i_port_select)   , 
				    .i_data_dir      (i_data_dir)      , 
				    .i_data_transmit (i_data_transmit) , 
				    .o_data_received (o_data_received) ,
				    .io_pin_states   (io_pin_states)   );

always @(posedge i_clk) begin
	
end

endmodule
