/******************************************************************************
* Name:    adc.c
* Description: STM32 adc functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
void AdcInit(void){
	//initialize gpioA
	// initialize ADC Clock
	// initialize AFIO Clock
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN;
		
	//initialize the pins
	GPIOA->CRL &= 0xFFFFFFF9;
	//turn on the ADC
	ADC1->CR2 = ADC_CR2_ADON;
}

uint32_t conversion(uint16_t channel){
	//set channel
	ADC1->SQR3 = channel;	
	ADC1->CR2 = ADC_CR2_ADON;
	ADC1->SQR3 = channel;
	uint16_t eoc = 0;
	do {
		eoc = ADC1->SR >> 1 & 1;
	} while (eoc == 0);
	
	//read and return data
	return ADC1->DR;
}
