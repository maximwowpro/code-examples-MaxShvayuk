module arithmetic_module
(
	input logic [31:0] a,
	input logic [31:0] b,
	input logic arithmetic_ctrl, sign_ctrl,
	
	output logic [31:0] y,
	output logic overflow
); 

logic cout;

logic ovf_1;
logic ovf_2;
logic ovf_3;
logic ovf_4;

always @*
begin 
	if(0===arithmetic_ctrl)
		{cout,y}=a+b;
	else
		{cout,y}=a-b;
	
	ovf_1=(~a[31])&(~b[31])&(~arithmetic_ctrl)&(y[31]);
	
	ovf_2=(~a[31])&(b[31])&(arithmetic_ctrl)&(y[31]);
	
	ovf_3=(a[31])&(b[31])&(~arithmetic_ctrl)&(~y[31]);
	
	ovf_4=(a[31])&(~b[31])&(arithmetic_ctrl)&(~y[31]);
	
	
	
	overflow=(~sign_ctrl&cout)|(sign_ctrl&(ovf_1|ovf_2|ovf_3|ovf_4));

end
endmodule