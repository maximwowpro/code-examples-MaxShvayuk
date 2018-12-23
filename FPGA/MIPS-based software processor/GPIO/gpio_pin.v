module gpio_one_pin (i_clk, i_enable, i_data_dir, i_data_transmit, o_data_received, io_pin_state);

input             i_clk;	/* clock signal 					*/
input          i_enable;		/* 1 == enable, 0 == disable				*/
input  	     i_data_dir; 	/* set direction of the bit of GPIO pin			*/
input   i_data_transmit; 	/* data, to transmit from GPIO pin (data OUT)	  	*/

inout      io_pin_state; 	/* logic states which presents at GPIO pin 		*/

output   o_data_received; 	/* data, received from GPIO pin    (data IN)		*/

reg first, second;

//tri_buf tri_bufs_obj (.i_in(first), .o_out(io_pin_state), .i_enable(i_data_dir));

assign io_pin_state = (i_data_dir && i_enable) ? first : 1'bz;

assign o_data_received = (i_enable) ? second : 1'bz;

always @(posedge i_clk)
begin	
	if (1 === i_enable) begin
		second <= io_pin_state;
		first  <= i_data_transmit;
	end
end

endmodule
