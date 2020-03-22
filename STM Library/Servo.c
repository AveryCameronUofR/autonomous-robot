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
	setupExti2PA();
	setupExti3PA();
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
		Delay(12);
		GPIOA->ODR |= 0x00000004;
		Delay(60);
		GPIOA->ODR &=  0xFFFFFFFB;
		
		LcdFirstLine();
		reg_out(time);
		LcdSecondLine();
		reg_out(time);
		
		//pull signall low for 18ms
		//pull high and wait 20-40 us
		//dht sends response signal 80us
		//dht pulls up voltage for 80us, 
		//every bit 50us low voltage, 40 bits totall 
	}
}
void SysTick_Handler(){
	GPIOC->ODR ^= GPIO_ODR_ODR8;
	if (count == 1){
		time += 1;
	}
}

void EXTI3_IRQHandler(){
	count = 0;
	EXTI->PR |= EXTI_PR_PR3;
	LcdFirstLine();
	reg_out(time);
	LcdSecondLine();
	reg_out(time);
	time = 0;
}

void EXTI2_IRQHandler(){
	count = 1;
	EXTI->PR |= EXTI_PR_PR2;
}
