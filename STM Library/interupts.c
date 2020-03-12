/******************************************************************************
 * Name:    interupts.c
 * Description: STM32 interupt initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
 #include "stm32f10x.h"
 #include "interupts.h"
 
 void enableAFIO(void){
	 
 }
 
 void enableExti0PA(void) {
	 AFIO->EXTICR[0] =0;
 }
 
 void unmaskExti0(void) {
	 EXTI->IMR |= 0x1;
 }
 
 void fallingEdgeExti0(void){
	 EXTI->FTSR |= 0x1;
 }
 
 void unmaskNvicExti0(void){
	 NVIC->ISER[0] |= 0x40;
 }
 
 void setupExti0PA(void){
	 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	 AFIO->EXTICR[0] =0;
	 EXTI->IMR |= 0x1;
	 EXTI->FTSR |= EXTI_FTSR_TR0;
	 NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
 }
 
 void setupSysTick(void){
	 SysTick->CTRL = 0x0;
	 SysTick->VAL= 0x0;
	 SysTick->LOAD=0xB71B00;
	 SysTick->CTRL =0x07;
 }
 