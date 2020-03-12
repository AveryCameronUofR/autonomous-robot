 #include "clock.h"
 #include "gpio.h"
 #include "lcd.h"
 int main(){
	 ClockInit();
	 GpioClockInit();
	 LcdInit();
	 GPIOC->CRH &= 0xFFF44444;
	 while (1){
	   LcdFirstLine();
		 uint8_t ir1 = ReadIR(1);
		 uint8_t ir2 = ReadIR(2);
		 uint8_t ir3 = ReadIR(3);
		 uint8_t ir4 = ReadIR(4);
		 uint8_t ir5 = ReadIR(5);
		 PrintHexToLcd(ir1);
		 LcdSecondLine();
		 PrintHexToLcd(ir2);
		 Delay(5000000);
	 }
	 return 0;
 }