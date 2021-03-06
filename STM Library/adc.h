/******************************************************************************
 * Name:    adc.h
 * Description: STM32 adc functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
/**
* Name: AdcInit
* Input: None
* Return: None
*
* Description: 
* Initializes ADC 1
* Enables GPIOA clock, ADC Clock, AFIO Clock and sets Pin A0 to AF input
* 
*/
void AdcInit(void); 

/**
* Name: conversion
* Input: 
* 	uint8_t channel: ADC Channel to convert
* Return: 
* 	uint32_t: Converted ADC value for the input channel
*
* Description: 
* Takes in the channel to convert (Channel 1 is potentiometer)
* Waits for end of conversion signal, returns the data for the ADC Channel
*/
uint32_t ConvertAdcChannel(uint8_t channel);

/**
* Name: convert_motor_speed
* Input: 
* 	uint8_t channel: ADC Potentiometer Reading
* Return: 
* 	uint32_t: Converted Potentiometer Reading in Range 10-95
*
* Description: 
* This maps the Potentiometer reading between 10-95 for controlling the motors
*/
uint16_t convert_motor_speed (uint32_t potentiometer_reading);
