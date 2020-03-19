/******************************************************************************
* Name:    interrupts.c
* Description: STM32 interrupt initialization
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
#include "interrupts.h"

void setupExti0PA(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] =0;
	EXTI->IMR |= 0x1;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
}

void setupExti2PA(void){
	//starts the AFIO Clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Enable EXTI 2 
	AFIO->EXTICR[2] =0;
	//Unmask MR2
	EXTI->IMR |= 0x4;
	//Configure interupt to happen on rising edge
	EXTI->FTSR |= EXTI_FTSR_TR1;
	//Unmask EXTI2
	NVIC->ISER[0] |= NVIC_ISER_SETENA_8;
}

void setupExtiInterrupt(uint8_t exti, uint8_t pinGroup, uint16_t nvicMask){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Enable EXTI for pin group, A=0, B=1 etc
	AFIO->EXTICR[exti] =pinGroup;
	// Unmask MR
	EXTI->IMR |= exti<<1;
	//Configure iterrupt to happen on edge
	EXTI->RTSR |= 1;
	EXTI->FTSR |= 1;
	//unmask EXTI 
	NVIC->ISER[0] |= nvicMask;
}

void setupExti3PA(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Enable EXTI 3
	AFIO->EXTICR[2] =0;
	// Unmask MR3
	EXTI->IMR |= 0x8;
	//Configure iterrupt to happen on falling edge
	EXTI->FTSR |= EXTI_FTSR_TR0;
	//unmask EXTI3
	NVIC->ISER[0] |= NVIC_ISER_SETENA_9;
}

void setupSysTick(void){
	SysTick->CTRL = 0x0;
	SysTick->VAL= 0x0;
	SysTick->LOAD=0xB71B00;
	SysTick->CTRL =0x07;
}
