#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "interrupts.h"
uint8_t count = 0;
uint8_t count2 = 0;
int time = 0;
int main(){
	ClockInit();
	GpioClockInit();
	ConfigureLeds();
	LcdInit();
	ConfigureIrSensors();
	GPIOA->CRL &= 0xFFFF00FF;
	GPIOA->CRL |= 0x00003400;
	uint16_t period = 400;
	uint16_t pulsewidth = 15;
	Tim1Ch1PwmInit(period, pulsewidth);
	//Setup interupt on Pin A2 Rising Edge
	setupExtiInterrupt(2, 0, 1, NVIC_ISER_SETENA_8);
	//Setup interupt on Pin A3 Falling Edge
	setupExtiInterrupt(2, 0, 0, NVIC_ISER_SETENA_9);
	//setup systick interupt
	setupSysTick();
	uint8_t counted = 0;
	while (1){
		uint8_t ir1 = ReadIR(1);
		uint8_t ir2 = ReadIR(2);
		uint8_t ir3 = ReadIR(3);
		uint8_t ir4 = ReadIR(4);
		uint8_t ir5 = ReadIR(5);
		pulsewidth = 15;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);		 
		pulsewidth = 30;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);
		pulsewidth = 45;
		SetTim1DutyCycle(pulsewidth);
		Delay(5000000);
		//UltraSonic Sensor Code 
	
		GPIOA->ODR &= 0xFFFFFFF7;
		Delay(30);
		GPIOA->ODR |= 0x00000008;
		Delay(60);
		GPIOA->ODR &= 0xFFFFFFF7;
		Delay(1200);
		if (count == 1){
			counted = 1;
		} else {
			counted = 0;
		}
		if (counted == 0){
			LcdFirstLine();
			OutputRegisterValue(count);
			LcdSecondLine();
			OutputRegisterValue(count2);
		}
	}
 }
 
 void SysTick_Handler(){
	if(count == 1){
		time++;
	}
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
