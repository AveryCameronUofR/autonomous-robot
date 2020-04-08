#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "interrupts.h"
#include "adc.h"
#include <stdbool.h>
uint8_t count = 0;
uint8_t count2 = 0;
int time = 0;
int main(){
	ClockInit();
	GpioClockInit();
	ConfigureLeds();
	LcdInit();
	
	ConfigureIrSensors();
	
	
	/*
	GPIOA->CRL &=0xFFFFFF0F;
	GPIOA->CRL |=0x00000030;
	GPIOA->CRH &=0x0FFFFFFF;
	GPIOA->CRH |=0x30000000;
	*/
	//servo 
	uint16_t period = 400;
	uint16_t pulsewidth = 15;
	Tim1Ch1PwmInit(period, pulsewidth);
	
	AdcInit();
	uint32_t potentiometer =0;
	potentiometer = ConvertAdcChannel(2);
	uint16_t motorPulseWidth = 0;
	motorPulseWidth = convert_motor_speed(potentiometer);
	Tim4PwmInit(100, motorPulseWidth);
	ConfigureMotorInputs();
	
	// IR sensing code
	uint32_t threshold_to_count = 12500;
	uint32_t threshold_to_display = 25000;
	OutputRegisterValue(threshold_to_display);
	// the current number of navigation strips counted
	uint8_t strip_count = 0;
	
	// how long we've been on a black or white surface
	uint16_t ir_black_count = 0;
	uint16_t ir_white_count = 0;
	
	uint8_t last_ir1 = 0;
	uint8_t curr_ir1 = 0;
	
	bool counted_strip = false;
	bool should_display = false;

	while (1){
		potentiometer = ConvertAdcChannel(2);
		motorPulseWidth = convert_motor_speed(potentiometer);
		MoveForward();
		curr_ir1 = ReadIR(1);
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
			if (curr_ir1 == last_ir1) 
			{
				// update the right counter
				curr_ir1 == 1 ? ir_black_count++ : ir_white_count++;
				
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
		last_ir1 = curr_ir1;
		uint8_t ir2 = ReadIR(2);
		uint8_t ir3 = ReadIR(5);
		
		if (ir2 != 1){
			TurnLeft();
			Delay(2500000);
		}
		
		motorPulseWidth = convert_motor_speed(0);
		SetTim4DutyCycle(motorPulseWidth);
		pulsewidth = 15;
		SetTim1DutyCycle(pulsewidth);
		Delay(7000000);		 
		pulsewidth = 30;
		SetTim1DutyCycle(pulsewidth);
		Delay(7000000);
		pulsewidth = 45;
		SetTim1DutyCycle(pulsewidth);
		Delay(8000000);
		//UltraSonic Sensor Code 
	  /*
		GPIOA->ODR &= 0xFFFFFFFB;
		Delay(30);
		GPIOA->ODR |= 0x00000004;
		Delay(60);
		GPIOA->ODR &= 0xFFFFFFFB;
		Delay(1200);
		count = 0;
		
		LcdFirstLine();
		UpdateLeds(0x2);
		
		OutputRegisterValue(GPIOA->ODR);
		*/
	}
 }
 
 void SysTick_Handler(){
 }

 void EXTI2_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR2;
	count += 1;
	time = 0;
 }
 
  void EXTI3_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR3;
	count2 += 1;
 }
