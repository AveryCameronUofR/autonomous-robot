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

void GpioClockInit(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
}

void ConfigureLeds(void){
	//configures PA9 to PA12 to general purpose output, LED output
	GPIOA->CRH &= 0xFFF0000F;
	GPIOA->CRH |= 0x00033330;
	GPIOA->BSRR = 0x00001E00;
}

void UpdateLeds(uint16_t LED_val){
	uint16_t update_val;
	//update the value in PA9-12 (inverse logic requires the 0xE1FF)
	update_val = (LED_val<<9 & 0x1E00);
	uint16_t odrVal = GPIOA->ODR & 0xE1FF;
	GPIOA->ODR = odrVal | update_val;
}

void BlinkLeds(void){
	int delay = 600000;
	UpdateLeds(~GPIOA->ODR);
	Delay(delay);
}

void ConfigureIrSensors(){
	GPIOC->CRH &= 0xFFF44444;
}

uint8_t ReadIR(uint8_t sensor){
	return (GPIOC->IDR & (1 << (7+sensor))) >> (7+sensor);
}

void ConfigureMotorInputs(){
	//JTAG-DP Disabled and SW-DP Enabled
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	
	//Configure GPIO Output
	GPIOB->CRL |= GPIO_CRL_MODE3 | GPIO_CRL_MODE4;
	GPIOB->CRL &= ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4;
	
	GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15;
	GPIOB->CRH &= ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12 & ~GPIO_CRH_CNF13 & ~GPIO_CRH_CNF14 & ~GPIO_CRH_CNF15;
}

void MoveForward(void)
{
		GPIOB->ODR |= GPIO_ODR_ODR3;
		GPIOB->ODR &= ~GPIO_ODR_ODR4;
	
		GPIOB->ODR |= GPIO_ODR_ODR10;
		GPIOB->ODR &= ~GPIO_ODR_ODR11;
	
		GPIOB->ODR |= GPIO_ODR_ODR12;
		GPIOB->ODR &= ~GPIO_ODR_ODR13;
	
		GPIOB->ODR |= GPIO_ODR_ODR14;
		GPIOB->ODR &= ~GPIO_ODR_ODR15;
		TIM4->CCR1 = 75;
    TIM4->CCR2 = 75;
    TIM4->CCR3 = 75;
    TIM4->CCR4 = 75;
}
