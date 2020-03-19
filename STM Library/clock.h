/******************************************************************************
 * Name:    clock.h
 * Description: STM32 clock initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
//initialize system clock for m3 using RCC
void ClockInit(void);
void Delay(uint32_t);
