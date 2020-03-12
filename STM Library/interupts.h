/******************************************************************************
 * Name:    interupts.h
 * Description: STM32 interupt initialization
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
 
 void enableAFIO(void);
 void enableExti0PA(void);
 void unmaskExti0(void);
 void fallingEdgeExti0(void);
 void unmaskNvicExti0(void);
 
 
 void setupSysTick(void);
 void setupExti0PA(void);