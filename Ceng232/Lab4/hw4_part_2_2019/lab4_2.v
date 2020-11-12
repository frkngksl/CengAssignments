`timescale 1ns / 1ps

module lab4_2(
  input [1:0] mode,
  input [2:0] n_gasoline_pumps,      // for setup mode, max 6
  input [2:0] n_diesel_pumps,        // for setup mode, max 6
  input [3:0] fuel_amount,           // for add car mode, max 8
  input fuel_type,                   // for add car mode, gas(0) or diesel(1)
  input CLK, 

  output reg [0:5] pump_status,                // pump is working or not, max 6 pumps
  output reg is_gasoline_queue_not_full,       // gasoline queue full warning
  output reg is_diesel_queue_not_full,         // diesel queue full warning

  output reg [3:0] n_cars_in_gasoline_queue,   // to represent max 9 on 1 7-seg display
  output reg [3:0] n_cars_in_diesel_queue,     // to represent max 9 on 1 7-seg display

  output reg [7:0] total_gasoline_needed,      // to represent max 99 on 2 7-seg displays
  output reg [7:0] total_diesel_needed,        // to represent max 99 on 2 7-seg displays

  // reset these after one clock
  output reg invalid_gasoline_car,             // to lightup dot at an2
  output reg invalid_diesel_car,               // to lightup dot at an0
  output reg invalid_setup_params              // to lightup all dots
);

// write your code here
reg [3:0] memoryForPump [0:5];
reg [3:0] queueForDiesel [7:0];
reg [3:0] queueForGasoline [7:0];
reg [3:0] frontForGasoline;
reg [3:0] backForGasoline;
reg [3:0] backForDiesel;
reg [3:0] frontForDiesel;
reg [2:0] gasolinePump;
reg [2:0] dieselPump;
reg setupDoneFlag;
reg added;
integer j;
initial begin
added = 0;
memoryForPump[0] = 0;
memoryForPump[1] = 0;
memoryForPump[2] = 0;
memoryForPump[3] = 0;
memoryForPump[4] = 0;
memoryForPump[5] = 0;
pump_status = 6'b000000;
is_gasoline_queue_not_full = 0;
is_diesel_queue_not_full = 0;
n_cars_in_gasoline_queue = 4'b1111;
n_cars_in_diesel_queue = 4'b1111;
total_gasoline_needed = 8'b11111111;
total_diesel_needed = 8'b11111111;
invalid_gasoline_car = 0;
invalid_diesel_car = 0;
invalid_setup_params = 0;
queueForDiesel[7] = 0;
queueForDiesel[6] = 0;
queueForDiesel[5] = 0;
queueForDiesel[4] = 0;
queueForDiesel[3] = 0;
queueForDiesel[2] = 0;
queueForDiesel[1] = 0;
queueForDiesel[0] = 0;
queueForGasoline[7] = 0;
queueForGasoline[6] = 0;
queueForGasoline[5] = 0;
queueForGasoline[4] = 0;
queueForGasoline[3] = 0;
queueForGasoline[2] = 0;
queueForGasoline[1] = 0;
queueForGasoline[0] = 0;
frontForDiesel = 0;
backForDiesel = 7;
frontForGasoline = 0;
backForGasoline = 7;
setupDoneFlag = 0;
gasolinePump = 0;
dieselPump = 0;
end
always@(posedge CLK)
	begin
	if(mode == 2'b10 || mode == 2'b11)
		begin
			if(n_gasoline_pumps > 6)
				begin
				invalid_diesel_car =0;
				invalid_gasoline_car=0;
				invalid_setup_params = 1;
				end
			else if(n_diesel_pumps > 6)
				begin
				invalid_diesel_car =0;
				invalid_gasoline_car=0;
				invalid_setup_params = 1;
				end
			else if(n_diesel_pumps+n_gasoline_pumps == 0 || n_diesel_pumps+n_gasoline_pumps > 6)
				begin
				invalid_diesel_car =0;
				invalid_gasoline_car=0;
				invalid_setup_params = 1;
				end
			else 
				begin
				for(j=0;j<6;j=j+1)
					begin
					pump_status[j] = 0;
					end
				invalid_setup_params = 0;
				invalid_diesel_car =0;
				invalid_gasoline_car=0;
				for(j=0;j<6;j=j+1)
					begin
						if(j < (n_gasoline_pumps+n_diesel_pumps))
							begin
							pump_status[j] = 1;
							end
					end
				queueForDiesel[7] = 0;
				queueForDiesel[6] = 0;
				queueForDiesel[5] = 0;
				queueForDiesel[4] = 0;
				queueForDiesel[3] = 0;
				queueForDiesel[2] = 0;
				queueForDiesel[1] = 0;
				queueForDiesel[0] = 0;
				queueForGasoline[7] = 0;
				queueForGasoline[6] = 0;
				queueForGasoline[5] = 0;
				queueForGasoline[4] = 0;
				queueForGasoline[3] = 0;
				queueForGasoline[2] = 0;
				queueForGasoline[1] = 0;
				queueForGasoline[0] = 0;
				memoryForPump[0] = 0;
				memoryForPump[1] = 0;
				memoryForPump[2] = 0;
				memoryForPump[3] = 0;
				memoryForPump[4] = 0;
				memoryForPump[5] = 0;
				if(n_diesel_pumps == 0)
					begin
						n_cars_in_diesel_queue = 4'b1111;
						total_diesel_needed = 8'b11111111;
						is_gasoline_queue_not_full= 1;
						n_cars_in_gasoline_queue = 0;
						is_diesel_queue_not_full= 0;
						total_gasoline_needed = 0;
						setupDoneFlag=1;
					end
				else if(n_gasoline_pumps == 0)
					begin
						n_cars_in_gasoline_queue = 4'b1111;
						total_gasoline_needed = 8'b11111111;
						is_gasoline_queue_not_full=0;
						is_diesel_queue_not_full=1;
						n_cars_in_diesel_queue = 0;
						total_diesel_needed = 0;
						setupDoneFlag=1;
					end
				else
					begin
						is_gasoline_queue_not_full=1;
						is_diesel_queue_not_full=1;
						n_cars_in_gasoline_queue = 0;
						n_cars_in_diesel_queue = 0;
						total_gasoline_needed = 0;
						total_diesel_needed = 0;
						setupDoneFlag=1;
					end
				gasolinePump = n_gasoline_pumps;
				dieselPump = n_diesel_pumps;
				frontForGasoline = 0;
				frontForDiesel = 0;
				backForGasoline = 7;
				backForDiesel = 7;
				end
		end
	else if(mode == 2'b00)
		begin
		if(setupDoneFlag)
			begin
			invalid_setup_params = 0;
			invalid_gasoline_car = 0;
			invalid_diesel_car = 0;
			for(j=0;j<6;j=j+1)
				begin
				if(j<gasolinePump)
					begin
					if(pump_status[j] == 0)
						begin
						memoryForPump[j] = memoryForPump[j] - 1;
						total_gasoline_needed = total_gasoline_needed - 1;
						if(memoryForPump[j] == 0) 
							begin
							pump_status[j] = 1;
							end
						end
					else if(pump_status[j] == 1)
						begin
							if(n_cars_in_gasoline_queue>0)
							begin
							pump_status[j] = 0;
							memoryForPump[j] = queueForGasoline[frontForGasoline];
							frontForGasoline = (frontForGasoline+1);
							if(frontForGasoline == 8) frontForGasoline = 0;
							n_cars_in_gasoline_queue = n_cars_in_gasoline_queue - 1;
							is_gasoline_queue_not_full = 1;
							end
						end
					end	
				end
				for(j=0;j<6;j=j+1)
				begin
				if(j>=gasolinePump && (j < dieselPump+gasolinePump))
					begin
					if(pump_status[j] == 0)
						begin
						memoryForPump[j] = memoryForPump[j] - 1;
						total_diesel_needed = total_diesel_needed - 1;
						if(memoryForPump[j] == 0)
							begin
							pump_status[j] = 1;
							end
						end
					else if(pump_status[j] == 1)
						begin
						if(n_cars_in_diesel_queue>0)
							begin
							pump_status[j] = 0;
							memoryForPump[j] = queueForDiesel[frontForDiesel];
							frontForDiesel = (frontForDiesel+1);
							if(frontForDiesel == 8) frontForDiesel = 0;
							n_cars_in_diesel_queue = n_cars_in_diesel_queue -1 ;
							is_diesel_queue_not_full = 1;
							end
						end
					end			
				end
			end
		end
	else if(mode == 2'b01)
		begin
		invalid_gasoline_car = 0;
		invalid_diesel_car = 0;
		added = 0;	
		if(setupDoneFlag)
			begin
			if(gasolinePump == 0 && fuel_type == 0) invalid_gasoline_car = 1;
			else if(fuel_type == 0 && fuel_amount == 0) invalid_gasoline_car = 1;
			else if(fuel_type == 0 && fuel_amount > 8) invalid_gasoline_car = 1;
			else if(dieselPump == 0 && fuel_type == 1) invalid_diesel_car = 1;
			else if(fuel_type == 1 && fuel_amount == 0) invalid_diesel_car = 1;
			else if(fuel_type == 1 && fuel_amount > 8) invalid_diesel_car = 1;
			for(j=0;j<6;j=j+1)
				begin
				if(j<gasolinePump)
					begin
					if(pump_status[j] == 0)
						begin
						memoryForPump[j] = memoryForPump[j] - 1;
						total_gasoline_needed = total_gasoline_needed - 1;
						if(memoryForPump[j] == 0) 
							begin
							pump_status[j] = 1;
							end
						end
					else if(pump_status[j] == 1)
						begin
							if(n_cars_in_gasoline_queue>0)
							begin
							pump_status[j] = 0;
							memoryForPump[j] = queueForGasoline[frontForGasoline];
							frontForGasoline = (frontForGasoline+1);
							if(frontForGasoline == 8) frontForGasoline = 0;
							n_cars_in_gasoline_queue = n_cars_in_gasoline_queue - 1;
							is_gasoline_queue_not_full = 1;
							end
							else if(n_cars_in_gasoline_queue == 0 && added == 0 && fuel_type == 0 && invalid_gasoline_car == 0)
							begin
							pump_status[j] =0;
							memoryForPump[j] = fuel_amount;
							total_gasoline_needed = total_gasoline_needed + fuel_amount;
							added = 1;
							end
						end
					end
				end
			for(j=0;j<6;j=j+1)
				begin
				if(j>=gasolinePump && (j < dieselPump+gasolinePump))
					begin
					if(pump_status[j] == 0)
						begin
						memoryForPump[j] = memoryForPump[j] - 1;
						total_diesel_needed = total_diesel_needed - 1;
						if(memoryForPump[j] == 0)
							begin
							pump_status[j] = 1;
							end
						end
					else if(pump_status[j] == 1)
						begin
						if(n_cars_in_diesel_queue>0)
							begin
							pump_status[j] = 0;
							memoryForPump[j] = queueForDiesel[frontForDiesel];
							frontForDiesel = (frontForDiesel+1);
							if(frontForDiesel == 8) frontForDiesel = 0;
							n_cars_in_diesel_queue = n_cars_in_diesel_queue -1 ;
							is_diesel_queue_not_full = 1;
							end
						else if(n_cars_in_diesel_queue == 0 && added == 0 && fuel_type == 1 && invalid_diesel_car == 0)
							begin
							pump_status[j] = 0;
							memoryForPump[j] = fuel_amount;
							total_diesel_needed = total_diesel_needed + fuel_amount;
							added = 1;
							end
						end
					end	
				end
			if(fuel_type == 0 && n_cars_in_gasoline_queue == 8) invalid_gasoline_car=1;
			else if(fuel_type == 1 && n_cars_in_diesel_queue == 8) invalid_diesel_car = 1;
			if(fuel_type == 0 && invalid_gasoline_car == 0 && added == 0) 
				begin
				backForGasoline = (backForGasoline+1);
				if(backForGasoline == 8) backForGasoline = 0;
				queueForGasoline[backForGasoline] = fuel_amount;
				total_gasoline_needed = total_gasoline_needed +fuel_amount;
				n_cars_in_gasoline_queue = n_cars_in_gasoline_queue + 1;
				if(n_cars_in_gasoline_queue == 8) is_gasoline_queue_not_full = 0;
				else is_gasoline_queue_not_full = 1;
				end
			else if(fuel_type == 1 && invalid_diesel_car == 0 && added == 0)
				begin
				backForDiesel = (backForDiesel+1);
				if(backForDiesel == 8) backForDiesel = 0;
				queueForDiesel[backForDiesel] = fuel_amount;
				total_diesel_needed = total_diesel_needed + fuel_amount;
				n_cars_in_diesel_queue = n_cars_in_diesel_queue + 1;
				if(n_cars_in_diesel_queue == 8) is_diesel_queue_not_full = 0;
				else is_diesel_queue_not_full = 1;
				end					
			end
		end	
	end
endmodule
