/******************************************************************************
 * Name:    autonomous.c
 * Description: STM32 Robot Controller, calls general setup and control methods
 * Version: V1.00
 * Authors: Avery Cameron, Raymond Knorr
 *
 *****************************************************************************/

#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "adc.h"
#include <stdbool.h>
int main(){
	//Setup clocks, Lcd and Inputs
	ClockInit();
	GpioClockInit();
	LcdInit();
	LcdClear();
	ConfigureSwitches();
	ConfigureIrSensors();
	ConfigureLeds();
	
	//Configure PWM for Servo
	uint16_t period = 400;
	uint16_t pulsewidth = 15;
	Tim1Ch1PwmInit(period, pulsewidth);
	
	//Initialize Potentiometer on PA2
	AdcInit();
	uint32_t potentiometer =0;
	potentiometer = ConvertAdcChannel(2);
	
	//Use the Potentiometer for Motor Pulsewidth Value
	uint16_t motorPulseWidth = 0;
	motorPulseWidth = convert_motor_speed(potentiometer);
	
	//Motor Configuration on Tim 4 PWM
	Tim4PwmInit(100, motorPulseWidth);
	ConfigureMotorInputs();
	
	// IR sensing code
	uint32_t threshold_to_count = motorPulseWidth * 2 + 50;
	uint32_t threshold_to_display = motorPulseWidth * 2 + 2000;
	uint32_t threshold_to_stop = motorPulseWidth * 2 + 5000;
	
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
			//Reverse
			MoveBackward();
			Start(motorPulseWidth);
			Delay(motorPulseWidth * 10000 + 500000);
			Stop(motorPulseWidth);
			//Turn
			TurnLeft();
			Start(motorPulseWidth);
			Delay(motorPulseWidth * 35000 + 500000);
			Stop(motorPulseWidth);
			//Resume Forward
			MoveForward();
			Start(motorPulseWidth);
		} else {
			MoveForward();
			Start(motorPulseWidth);
		}
		
		//Read the line sensor
		curr_ir2 = ReadIR(2);
		if (ir_white_count > threshold_to_display && should_display == true) 
		{
			// this is where to display to lcd
			LcdFirstLine();
			//Strip Count counts one extra line, subtract this for the correct number of lines
			strip_count = strip_count -1;
			
			//Update LEDs (led 1 for 1, LED 2 for 2, LED 3 for 3
			OutputRegisterValue(strip_count);
			if (strip_count == 1){
				UpdateLeds(~1);
			} else if (strip_count == 2){
				UpdateLeds(~2);
			}	else if (strip_count == 3){
				UpdateLeds(~4);
			}					
			
			//reset line counting variables
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
				if (ir_black_count >= threshold_to_stop && exited_start_area){
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
		
		//Object Detected by the IR Sensor 1
		uint8_t ir1 = ReadIR(1);
		if (ir1 != 1) {
			Stop(motorPulseWidth);
			MoveBackward();
			Start(motorPulseWidth);
			Delay(motorPulseWidth * 10000 + 500000);
			Stop(motorPulseWidth);
			TurnLeft();
			Start(motorPulseWidth);
			Delay(motorPulseWidth * 35000 + 500000);
			Stop(motorPulseWidth);
			MoveForward();
			Start(motorPulseWidth);
		} else {
			MoveForward();
			Start(motorPulseWidth);
		}
	
		//Move the Servo
		pulsewidth = 30;
		SetTim1DutyCycle(pulsewidth);
		
		//Make sure home zone has not been reached
		if (course_completed){
			//Exit the Loop
			Stop(motorPulseWidth);
			break;
		}
	}
}
 

