/******************************************************************************
 * Name:    usart.c
 * Description: USART Functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
	#include "stm32f10x.h"
   void UsartInit(){
		 //gpiob, usart3, afio clocks
		 RCC->APB2ENR |=  RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		 RCC->APB1ENR |=  RCC_APB1ENR_USART3EN;
		 USART3->CR1 |= USART_CR1_UE;
		 GPIOB->CRH &= 0xFFFFF0FF;
		 GPIOB->CRH |= 0x00000B00;
	 }
	 
	 void ConfigureUsart(){
		 USART3->BRR = 0x9C4;
		 USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;
	 }
	 
	 uint16_t SendData(uint16_t data){
		 uint16_t lineFree = USART3->SR & 0x80;
		 if(lineFree == 0x80){
			 USART3->DR = data;
			 return 1;
		 }
		 return 0;
	 }
	 
	 uint16_t readData(){
		 uint16_t dataReceived = USART3->SR & 0x10;
		 if (dataReceived == 0x10){
			 return USART3->DR;
		 }
		 return 0;
	 }