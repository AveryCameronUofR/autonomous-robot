/******************************************************************************
 * Name:    clock.c
 * Description: STM32 clock initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
 #include "stm32f10x.h"
 #include "clock.h"
 
 void ClockInit(void){	 
	 //No mco visibility to free up PA8
	 //pll mul of 3 for 24mhz clock, pllsrc on
	 //pll selected as system clock
	 RCC->CFGR = 0x00050002;
	 
	 //turns on pll, hse, 8 is default, hsion on 
	 RCC->CR = 0x01010081;
	 
	 uint32_t temp = 0x00;
	 //wait for PLL to stabalize
	 while (temp != 0x02000000)  // Wait for the PLL to stabilize
   {
        temp = RCC->CR & 0x02000000; //Check to see if the PLL lock bit is set
   }
	 
	 // Write a 0xB ( 1011b ) into the configuration and mode bits for PA8 (AFIO)
   // GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 ;
   // GPIOA->CRH &= ~GPIO_CRH_CNF8_0 ;
 }
 
 
 //about 6000 gives a delay of 1 ms
 void Delay(uint32_t count)
 {
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
 }
