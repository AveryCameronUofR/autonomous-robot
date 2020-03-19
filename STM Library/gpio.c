/******************************************************************************
* Name:    gpio.h
* Description: STM32 gpio functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
#include "gpio.h"
#include "clock.h"
//initializes GPIO Clock for Port A,B, C and D
void GpioClockInit(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
}

void led_IO_init (void)
{
    //Set the config and mode bits for Port C bit 9 and 8 so they will
    // be push-pull outputs (up to 50 MHz)
    GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8 ;
    GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8 ;
}

void ConfigureLeds(void){
	//configures PA9 to PA12 to general purpose output, LED output
	GPIOA->CRH &= 0xFFF0000F;
	GPIOA->CRH |= 0x00033330;
}

void UpdateLeds(uint16_t LED_val){
	uint16_t update_val;
	update_val = (LED_val<<9 & 0x1E00);
	uint16_t odrVal = GPIOA->ODR & 0xE1FF;
	GPIOA->ODR = odrVal | update_val;
}

void Blink(void){
	int delay = 600000;
	UpdateLeds(~GPIOA->ODR);
	Delay(delay);
}

uint8_t ReadIR(uint8_t sensor){
	return (GPIOC->IDR & (1 << (7+sensor))) >> (7+sensor);
}
