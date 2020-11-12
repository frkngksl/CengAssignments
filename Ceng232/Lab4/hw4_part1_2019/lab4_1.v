`timescale 1ns / 1ps
module MaskROM (input [3:0] RomAddress, output reg[7:0] RomDataOut);
/*  Please write your code below  */
	reg[7:0] memword[0:15];
	initial begin 
	memword[0] = 8'b00000000;
	memword[1] = 8'b00001111;
	memword[2] = 8'b00011110;
	memword[3] = 8'b00110000;
	memword[4] = 8'b01010000;
	memword[5] = 8'b01100110;
	memword[6] = 8'b01101010;
	memword[7] = 8'b01111110;	
	memword[8] = 8'b10000001;
	memword[9] = 8'b10100000;
	memword[10] = 8'b10100110;
	memword[11] = 8'b10111101;
	memword[12] = 8'b11000000;
	memword[13] = 8'b11010000;
	memword[14] = 8'b11010011;
	memword[15] = 8'b11100110;
	end
	always@(RomAddress)
	begin
		RomDataOut = memword[RomAddress];
	end
	
/*  Please write your code above  */
endmodule


/*mode 0:read, 1:write*/																							
module RgbRAM (input Mode,input [3:0] RamAddress, input [23:0] RamDataIn,
					input [7:0] Mask,input [2:0] Op, input CLK, output reg [23:0] RamDataOut);
/*  Please write your code below  */
	reg[23:0] ramword[0:15];
	reg[7:0] first;
	reg[7:0] second;
	reg[7:0] third;
	initial begin 
	ramword[0] = 24'b000000000000000000000000;
	ramword[1] = 24'b000000000000000000000000;
	ramword[2] = 24'b000000000000000000000000;
	ramword[3] = 24'b000000000000000000000000;
	ramword[4] = 24'b000000000000000000000000;
	ramword[5] = 24'b000000000000000000000000;
	ramword[6] = 24'b000000000000000000000000;
	ramword[7] = 24'b000000000000000000000000;
	ramword[8] = 24'b000000000000000000000000;
	ramword[9] = 24'b000000000000000000000000;
	ramword[10] = 24'b000000000000000000000000;
	ramword[11] = 24'b000000000000000000000000;
	ramword[12] = 24'b000000000000000000000000;
	ramword[13] = 24'b000000000000000000000000;
	ramword[14] = 24'b000000000000000000000000;
	ramword[15] = 24'b000000000000000000000000;
	first = 8'b00000000;
	second = 8'b00000000;
	third = 8'b00000000;
	end
always@(Mode or RamAddress)
	begin
		if(Mode == 0)
			begin
			RamDataOut = ramword[RamAddress];
			end
	end
always@(posedge CLK)
	begin
		if(Mode)
			begin
			case(Op)
				3'b000:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						first = first & Mask;
						second = second & Mask;
						third = third & Mask;
						ramword[RamAddress] = {first,second,third};
					end
				3'b001:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						first = first | Mask;
						second = second | Mask;
						third = third | Mask;
						ramword[RamAddress] = {first,second,third};
					end
				3'b010:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						first = first ^ Mask;
						second = second ^ Mask;
						third = third ^ Mask;
						ramword[RamAddress] = {first,second,third};
					end
				3'b011:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						if(first+Mask > 254) first = 255;
						else first = first+Mask;
						if(second+Mask > 254) second = 255;
						else second = second+Mask;
						if(third+Mask > 254) third = 255;
						else third = third+Mask;
						ramword[RamAddress] = {first,second,third};
					end
				3'b100:
					begin
					   first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						if(first < Mask) first = 8'b00000000;
						else first = first - Mask;
						if(second < Mask) second = 8'b00000000;
						else second = second - Mask;
						if(third < Mask) third = 8'b00000000;
						else third = third - Mask;
						ramword[RamAddress] = {first,second,third};
					end
				3'b101:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						if(first + 1 > 254) first = 255;
						else first = first+1;
						if(second + 1 > 254) second = 255;
						else second = second+1;
						if(third + 1 > 254) third = 255;
						else third = third+1;
						ramword[RamAddress] = {first,second,third};
					end
				3'b110:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						if(first < 2) first = 8'b00000000;
						else first = first-1;
						if(second < 2) second = 8'b00000000;
						else second = second-1;
						if(third  < 2) third = 8'b00000000;
						else third = third-1;
						ramword[RamAddress] = {first,second,third};
					end
				3'b111:
					begin
						first = RamDataIn[23:16];
						second = RamDataIn[15:8];
						third = RamDataIn[7:0];
						first = {first[6:0],first[7]};
						second = {second[6:0],second[7]};
						third = {third[6:0],third[7]};
						ramword[RamAddress] = {first,second,third};
					end	
				endcase		
			end
	end
/*  Please write your code above  */
endmodule


module RgbMaskModule(input Mode, input [3:0] Address, input [23:0] RGBin,input [2:0] Op,  input CLK, output wire [23:0] RGBout);
	
	/*  DO NOT edit this module  */
	
	wire [7:0]  romResult;

	MaskROM RO(Address, romResult);
	RgbRAM RA(Mode, Address, RGBin,romResult, Op, CLK, RGBout);
endmodule
