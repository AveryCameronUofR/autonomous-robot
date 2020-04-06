#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "interrupts.h"
#include "adc.h"
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
	
	while (1){
		MoveForward();
		uint8_t ir1 = ReadIR(1);
		uint8_t ir2 = ReadIR(2);
		uint8_t ir3 = ReadIR(5);
		
		LcdFirstLine();
		potentiometer = ConvertAdcChannel(2);
		motorPulseWidth = convert_motor_speed(potentiometer);
		SetTim4DutyCycle(motorPulseWidth);
		
		OutputRegisterValue(motorPulseWidth);
		pulsewidth = 15;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);
		pulsewidth = 30;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);
		pulsewidth = 45;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);
		Delay(5000000);
		
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
