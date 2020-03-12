 #include "clock.h"
 #include "gpio.h"
 #include "lcd.h"
 int main(){
	 ClockInit();
	 GpioClockInit();
	 uint16_t IR = ReadIR();
	 LcdInit();
	 GPIOC->CRH &= 0xFFF44444;
	 while (1){
	   LcdFirstLine();
		 uint16_t ir = ReadIR();
		 ir = ir >>8;
		 PrintHexToLcd(ir);
		 LcdSecondLine();
		 reg_out(GPIOC->IDR);
		 Delay(5000000);
	 }
	 return 0;
 }