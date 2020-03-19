#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "pwm.h"
#include "interrupts.h"
uint8_t count = 0;
int time = 0;
int main(){
	ClockInit();
	GpioClockInit();
	ConfigureLeds();
	led_IO_init();
	LcdInit();
	/*
	GPIOC->CRH &= 0xFFF44444;
	GPIOA->CRL &= 0xFFFF00FF;
	GPIOA->CRL |= 0x00003400;
	uint16_t period = 400;
	uint16_t pulsewidth = 15;
	PwmInit(period, pulsewidth);
	//setup systick interupt
	*/
	setupSysTick();
	//Setup interupt on Pin A3 Rising Edge
	setupExtiInterrupt(3, 0, NVIC_ISER_SETENA_9);
	while (1){
		/*
		uint8_t ir1 = ReadIR(1);
		uint8_t ir2 = ReadIR(2);
		uint8_t ir3 = ReadIR(3);
		uint8_t ir4 = ReadIR(4);
		uint8_t ir5 = ReadIR(5);
		pulsewidth = 15;
		setDutyCycle(pulsewidth);
		Delay(5000000);		 
		pulsewidth = 30;
		setDutyCycle(pulsewidth);
		Delay(5000000);
		pulsewidth = 45;
		setDutyCycle(pulsewidth);
		Delay(5000000);
		//UltraSonic Sensor Code 
	   */
		GPIOA->ODR &=  0xFFFFFFFB;
		Delay(600000);
		GPIOA->ODR |= 0x00000004;
		Delay(600000);
		GPIOA->ODR &=  0xFFFFFFFB;
		LcdFirstLine();
		reg_out(time);
		LcdSecondLine();
		reg_out(time);
	}
}
void SysTick_Handler(){
	GPIOC->ODR ^= GPIO_ODR_ODR8;
}

void EXTI3_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR3;
}
