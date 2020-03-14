/******************************************************************************
 * Name:    interupts.h
 * Description: STM32 interupt initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
 #include "stm32f10x.h"
 /*
 * Name: setupExtiInterupt
 * Inputs: 
 * 		exit: EXTI Interupt to configure, PX0=0, PX1=1, PX2=2 etc.
 *		pinGroup: Pin Group to configure, PA=0, PB=1, PC=2
 *		edgeDetection: Determines interupt trigger, falling or rising edge
 * 		nvicMask: NVIC entry to unmask (6 for EXTI0)
 * Return: None
 * Description:
 * Sets up an EXTI Interupt for the given pin number and pin group
 * Allows user to configure the interupt trigger and unmask the interupt
 */
 void setupExtiInterupt(uint8_t exti, uint8_t pinGroup, uint16_t edgeDetection, uint16_t nvicMask);
 
 void setupSysTick(void);
 void setupExti0PA(void);
 void setupExti2PA(void);
 void setupExti3PA(void);