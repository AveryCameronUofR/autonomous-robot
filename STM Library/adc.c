/******************************************************************************
 * Name:    adc.c
 * Description: STM32 adc functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
void AdcInit(void){
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN;
	
	//initialize the pins to AF input
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000009;
	//turn on the ADC
	ADC1->CR2 = ADC_CR2_ADON;
}

uint32_t ConvertAdcChannel(uint8_t channel){
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

uint16_t convert_motor_speed (uint32_t potentiometer_reading)
{
	// converts values from 0xfff-0x0 -> 0xa-0x5f or 10 - 95 (decimal)
	uint16_t output = 0xfff - potentiometer_reading;
	output = (uint16_t) (output / 48) + 10;
	return output;
}
