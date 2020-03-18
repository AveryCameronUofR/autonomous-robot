 #include "clock.h"
 #include "gpio.h"
 #include "lcd.h"
 #include "pwm.h"
 #include "interrupts.h"
 uint8_t count = 0;
 uint8_t count2 = 0;
 int time = 0;
 uint8_t edgeDetector = 1;
 int main(){
	 ClockInit();
	 GpioClockInit();
	 ConfigureLeds();
	 led_IO_init();
	 LcdInit();
	 GPIOC->CRH &= 0xFFF44444;
	 GPIOA->CRL &= 0xFFFF00FF;
	 GPIOA->CRL |= 0x00003400;
	 uint16_t period = 400;
	 uint16_t pulsewidth = 15;
	 PwmInit(period, pulsewidth);

	 //Setup interupt on Pin A3 Rising Edge
	 setupExtiInterrupt(2, 0, NVIC_ISER_SETENA_9);
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
		 setDutyCycle(pulsewidth);
		 Delay(5000000);		 
		 pulsewidth = 30;
		 setDutyCycle(pulsewidth);
		 Delay(5000000);
		 pulsewidth = 45;
		 setDutyCycle(pulsewidth);
		 Delay(5000000);
		 //UltraSonic Sensor Code 
	   
		 GPIOA->ODR &= 0xFFFFFFFB;
		 Delay(30);
		 GPIOA->ODR |= 0x00000004;
		 Delay(60);
		 GPIOA->ODR &= 0xFFFFFFFB;
		 LcdFirstLine();
		 reg_out(time);
		 LcdSecondLine();
		 reg_out(time);
	 }
	 return 0;
 }
 void SysTick_Handler(){
	 //if waiting for falling edge
		if(edgeDetector == 0){
			time++;
			
		}
		GPIOC->ODR ^= GPIO_ODR_ODR8;
 }
 
  void EXTI3_IRQHandler(){
	 EXTI->PR |= EXTI_PR_PR3;
	 edgeDetector ^= edgeDetector;
 }