/******************************************************************************
* Name:    pwm.h
* Description: PWM functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"

/*
* Name: Tim1Ch1PwmInit
* Input: 
* 	uint16_t Period: The period for PWM
*		uint16_t Pulsewidth The initial pulsewidth for PWM
* Output: None
*
* Description: 
* Takes in a period and sets up TIM4 channels 1 to 4 as PWM Output
* The PWM outputs of TIM 4 CH1-4 are located on pins PB6-9 on the STM32F100RB
* 
* Notes:
*/
void Tim1Ch1PwmInit(uint16_t, uint16_t); 

/*
* Name: Tim4PwmInit
* Input: 
*		uint16_t Period 
* Output: None
*
* Description: 
* Takes in a period and sets up TIM4 channels 1 to 4 as PWM Output
* The PWM outputs of TIM 4 CH1-4 are located on pins PB6-9 on the STM32F100RB
* 
* Notes: 
*/ 
void Tim4PwmInit(uint16_t);

/*
* Name: SetTim1DutyCycle
* Input: 
* 	uint16_t Pulsewidth: The new pulsewidth  
* Output: None
*
* Description: 
* Sets the pulsewidth for TIM1 CH 1
* Notes:
*/
void SetTim1DutyCycle(uint16_t);
