/******************************************************************************
 * Name:    clock.h
 * Description: STM32 clock initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
/**
* Name: ClockInit
* Input: None
* Return: None
*
* Initializes 24MHz clock for the STM32F100RB Board
*/
void ClockInit(void);

/**
* Name: Delay
* Input: 
* 	uint32_t: Value to Delay by
* Return: None
*
* Delays for the given amount of cycles,
* Note: 6000 is ~1ms of time
*/
void Delay(uint32_t);
