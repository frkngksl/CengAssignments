`timescale 1ns / 1ps

module df(
    input d,
    input f,
    input clk,
    output reg q
    );
    
    initial begin
        q = 0;
    end
	
    // write your code here

	always@(posedge clk)
	begin
		q<= (~d & ~f) | (q & ~d) | (~q & d & f);
	end
endmodule

module icplusplus(
		input d0,
		input f0,
		input d1,
		input f1,
		input clk,
		output q0,
		output q1,
		output y
		);
		df df_1(d0,f0,clk,q0);
		df df_2(d1,f1,clk,q1);
		assign y = q1 ~^ q0;
endmodule		