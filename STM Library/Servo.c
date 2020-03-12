 #include "clock.h"
 #include "gpio.h"
 #include "lcd.h"
 #include "pwm.h"
 int main(){
	 ClockInit();
	 GpioClockInit();
	 ConfigureLeds();
	 LcdInit();
	 GPIOC->CRH &= 0xFFF44444;
	 GPIOA->CRL &= 0xFFFF00FF;
	 GPIOA->CRL |= 0x00003400;
	 uint16_t period = 400;
	 uint16_t pulsewidth = 15;
	 PwmInit(period, pulsewidth);
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
	   LcdFirstLine();
		 GPIOA->ODR &= 0xFFFFFFF7;
		 Delay(30);
		 GPIOA->ODR |= 0x00000008;
		 Delay(60);
		 GPIOA->ODR &= 0xFFFFFFF7;
		 uint8_t input = 0;
		 int i=0;
		 while(input != 1){
			 input = GPIOA->IDR & GPIO_IDR_IDR2;
			 input = input >> 2;
			 i++;
		 }
		 reg_out(i);
		 LcdSecondLine();
		 reg_out((i/2)/29.1);
	 }
	 return 0;
 }