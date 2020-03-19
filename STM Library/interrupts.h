/******************************************************************************
* Name:    interrupts.h
* Description: STM32 interrupt initialization
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
/*
* Name: setupExtiinterrupt
* Inputs: 
* 		exit: EXTI interrupt to configure, PX0=0, PX1=1, PX2=2 etc.
*		pinGroup: Pin Group to configure, PA=0, PB=1, PC=2
*		edgeDetection: Determines interrupt trigger, falling or rising edge
*			1 for rising edge, 0 for falling edge
* 		nvicMask: NVIC entry to unmask (6 for EXTI0)
* Return: None
* Description:
* Sets up an EXTI interrupt for the given pin number and pin group
* Allows user to configure the interrupt trigger and unmask the interrupt
*/
void setupExtiInterrupt(uint8_t exti, uint8_t pinGroup, uint16_t edgeDetection, uint16_t nvicMask);

void setupSysTick(void);
void setupExti0PA(void);
void setupExti2PA(void);
void setupExti3PA(void);
