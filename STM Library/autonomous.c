#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "adc.h"
#include <stdbool.h>
int main(){
	ClockInit();
	GpioClockInit();
	ConfigureLeds();
	LcdInit();
	
	ConfigureSwitches();
	ConfigureIrSensors();
	
	//servo 
	uint16_t period = 400;
	uint16_t pulsewidth = 15;
	Tim1Ch1PwmInit(period, pulsewidth);
	
	AdcInit();
	uint32_t potentiometer =0;
	potentiometer = ConvertAdcChannel(2);
	uint16_t motorPulseWidth = 0;
	motorPulseWidth = convert_motor_speed(potentiometer);
	
	//Motor Configuration
	Tim4PwmInit(100, motorPulseWidth);
	ConfigureMotorInputs();
	
	// IR sensing code
	uint32_t threshold_to_count = 12500;
	uint32_t threshold_to_display = 25000;
	uint32_t thrshold_to_stop = 50000;
	
	OutputRegisterValue(threshold_to_display);
	// the current number of navigation strips counted
	uint8_t strip_count = 0;
	
	// how long we've been on a black or white surface
	uint16_t ir_black_count = 0;
	uint16_t ir_white_count = 0;
	
	uint8_t last_ir2 = 0;
	uint8_t curr_ir2 = 0;
	
	bool counted_strip = false;
	bool should_display = false;
	bool exited_start_area = false;
	bool course_completed = false;
	while (1){
		//Update the max motor speed
		potentiometer = ConvertAdcChannel(2);
		motorPulseWidth = convert_motor_speed(potentiometer);
		
		//If either of the limit switches are hit
		if (ReadSwitches() == 1){
			Stop(motorPulseWidth);
			MoveBackward();
			Start(motorPulseWidth);
			Delay(5000000);
			Stop(motorPulseWidth);
			TurnLeft();
			Start(motorPulseWidth);
			Delay(6500000);
			Stop(motorPulseWidth);
			MoveForward();
			Start(motorPulseWidth/2);
		} else {
			MoveForward();
			Start(motorPulseWidth/2);
		}
		
		curr_ir2 = ReadIR(2);
		if (ir_white_count > threshold_to_display && should_display == true) 
		{
			// this is where to display to lcd
			LcdFirstLine();
			OutputRegisterValue(strip_count);
			ir_black_count = 0;
			ir_white_count = 0;
			should_display = false;
			strip_count = false;
		} else {
			if (curr_ir2 == last_ir2) 
			{
				// update the right counter
				curr_ir2 == 1 ? ir_black_count++ : ir_white_count++;
				
				//If white is detected, we have left the start area
				if (curr_ir2 == 0){
					exited_start_area = true;
				}
				//If we have a large amount of black, we are back at the start
				if (ir_black_count >= thrshold_to_stop && exited_start_area){
					course_completed = true;
				}
				//Detected black for long enough, count add to count
				if (ir_black_count >= threshold_to_count && !counted_strip) 
				{
					counted_strip =  true;
					should_display = true;
					ir_black_count = 0;
					strip_count++;
				}
			} else 
			{
				ir_black_count = 0;
				ir_white_count = 0;
				counted_strip = false;
			}
		}
		last_ir2 = curr_ir2;
		
		//Object Detected by the IR Sensor
		uint8_t ir1 = ReadIR(1);
		if (ir1 != 1) {
			Stop(motorPulseWidth);
			MoveBackward();
			Start(motorPulseWidth);
			Delay(600000);
			Stop(motorPulseWidth);
			TurnLeft();
			Start(motorPulseWidth);
			Delay(5500000);
			Stop(motorPulseWidth);
			MoveForward();
			Start(motorPulseWidth/2.2);
		} else {
			MoveForward();
			Start(motorPulseWidth/2.2);
		}
	
		//Move the Servo
		pulsewidth = 30;
		SetTim1DutyCycle(pulsewidth);
		
		
		if (course_completed){
			//Exit the Loop
			break;
		}
	}
}
 

