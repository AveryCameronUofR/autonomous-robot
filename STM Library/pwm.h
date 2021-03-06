/******************************************************************************
* Name:    pwm.h
* Description: PWM functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"

/**
* Name: Tim1Ch1PwmInit
* Input: 
* 	uint16_t Period: The period for PWM
*		uint16_t Pulsewidth The initial pulsewidth for PWM
* Return: None
*
* Description: 
* Takes in a period and sets up TIM4 channels 1 to 4 as PWM Output
* The PWM outputs of TIM 4 CH1-4 are located on pins PB6-9 on the STM32F100RB
* 
* Notes:
*/
void Tim1Ch1PwmInit(uint16_t period, uint16_t pulsewidth); 

/**
* Name: Tim4PwmInit
* Input: 
*		uint16_t Period 
* Return: None
*
* Description: 
* Takes in a period and sets up TIM4 channels 1 to 4 as PWM Output
* The PWM outputs of TIM 4 CH1-4 are located on pins PB6-9 on the STM32F100RB
* 
* Notes: 
*/ 
void Tim4PwmInit(uint16_t period, uint16_t pulsewidth);

/**
* Name: SetTim1DutyCycle
* Input: 
* 	uint16_t Pulsewidth: The new pulsewidth  
* Return: None
*
* Description: 
* Sets the pulsewidth for TIM1 CH 1
* Notes:
*/
void SetTim1DutyCycle(uint16_t pulsewidth);

/**
* Name: SetTim4DutyCycle
* Input: 
* 	uint16_t Pulsewidth: The new pulsewidth  
* Return: None
*
* Description: 
* Sets the pulsewidth for all channels on TIM4 
* Notes:
*/
void SetTim4DutyCycle(uint16_t pulsewidth);

void motor_clock(void);
void motor_forward(void);
