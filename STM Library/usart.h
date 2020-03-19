/******************************************************************************
* Name:    usart.h
* Description: USART functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
void UsartInit(); 
void ConfigureUsart(); 
uint16_t SendData(uint16_t data);
uint16_t readData();
