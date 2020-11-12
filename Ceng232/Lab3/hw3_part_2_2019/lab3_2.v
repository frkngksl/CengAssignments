`timescale 1ns / 1ps 
module lab3_2(
			input[3:0] number,
			input CLK, 
			input selection,
			input mode,
			input clear,
			output reg [7:0] digit1,
			output reg [7:0] digit0,
			output reg [7:0] count1,
			output reg [7:0] count0,
			output reg warning
    );
   //Modify the lines below to implement your design .
	reg[3:0] count0forPrime;
	reg[3:0] count1forPrime;
	reg[3:0] count0forNonPrime;
	reg[3:0] count1forNonPrime;
	initial begin
			digit1 = 0;
			digit0 = 0;
			count1 = 0;
			count0 = 0;
			warning = 0;
			count0forPrime=0;
			count1forPrime=0;
			count0forNonPrime=0;
			count1forNonPrime=0;
	end	
	always@(posedge CLK)
	begin
	if(clear)
		begin
		digit1=0;
		digit0=0;
		count1=0;
		count0=0;
		warning=0;
		count0forPrime=0;
		count1forPrime=0;
		count0forNonPrime=0;
		count1forNonPrime=0;
		end // tamam
	else
		begin
		if(selection == 1'b0)
			begin
				if((number[2]&(~number[1])&number[0])|((~number[3])&number[2]&number[0])|number[1]&number[0]&(~number[2])|(number[1]&(~number[3])&(~number[2])))
					begin
					warning = 0;
					if(mode)
						begin
						case(number)
							4'b0010:
								begin
								digit0 = number;
								digit1 = 4'b0011;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
							4'b0011:
								begin
								digit0 = number;
								digit1 = 4'b0101;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
							4'b0101:
								begin
								digit0 = number;
								digit1 = 4'b0111;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
							4'b0111:
								begin
								digit0 = number;
								digit1 = 4'b1011;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
							4'b1011:
								begin
								digit0 =number;
								digit1 = 4'b1101;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
							4'b1101:
								begin
								digit0 = number;
								digit1 = 4'b0010;
								count0 = count0forPrime;
								if(count1forPrime == 9)
									begin
									count1forPrime = 0;
									count1=0;
									end
								else
									begin
									count1forPrime = count1forPrime + 1;
									count1 = count1forPrime;
									end
								end
						endcase
						end //mode 1 op tamam 
					else // mode 0 kýsmý
						begin
						case(number)
							4'b0010:
								begin
								digit0 = number;
								digit1 = 4'b1101;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
							4'b0011:
								begin
								digit0 = number;
								digit1 = 4'b0010;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
							4'b0101:
								begin
								digit0 = number;
								digit1 = 4'b0011;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
							4'b0111:
								begin
								digit0 = number;
								digit1 = 4'b0101;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
							4'b1011:
								begin
								digit0 =number;
								digit1 = 4'b0111;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
							4'b1101:
								begin
								digit0 = number;
								digit1 = 4'b1011;
								count1 = count1forPrime;
								if(count0forPrime == 9)
									begin
									count0forPrime = 0;
									count0=0;
									end
								else
									begin
									count0forPrime = count0forPrime + 1;
									count0 = count0forPrime;
									end
								end
						endcase
						end // mode 0 sonu 
				end 
				else
					begin
					warning = 1;
					end // prime sonu
			end
		else //selection 1
			begin
			if((number[2]&(~number[1])&number[0])|((~number[3])&number[2]&number[0])|number[1]&number[0]&(~number[2])|(number[1]&(~number[3])&(~number[2])))
				begin
				warning = 1;
				end
			else
				begin
				warning = 0;
				if(mode)
					begin
					digit0 = number;
					digit1 = (number << 1);
					digit1[4] = 0;
					count0 = count0forNonPrime;
					if(count1forNonPrime == 9)
						begin
						count1forNonPrime = 0;
						count1 = 0;
						end
					else
						begin
						count1forNonPrime = count1forNonPrime +1;
						count1 = count1forNonPrime;
						end
					end
				else // mode 0
					begin
					digit0 = number;
					digit1 = (number >> 1);
					count1 = count1forNonPrime;
					if(count0forNonPrime == 9)
						begin
						count0forNonPrime = 0;
						count0 = 0;
						end
					else
						begin
						count0forNonPrime = count0forNonPrime +1;
						count0 = count0forNonPrime;
						end
					end
				end
			end
		end
	end
endmodule