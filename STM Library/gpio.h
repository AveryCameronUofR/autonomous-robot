/******************************************************************************
* Name:    gpio.h
* Description: STM32 gpio functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"

//initializes clocks for gpio a,b,c
void GpioClockInit(void);
void led_IO_init (void);
//configures the led pins for output
void ConfigureLeds(void);
 
//Updates leds based on given value
void UpdateLeds(uint16_t);
//Blinks all 4 leds
void Blink(void);
 
/**
* Name: ReadIR
* Input: IR Sensor to detect
* Output: IR Sensor Output
*
* Input is a number from 1 to 5 
* for the 5 IR Sensors on the board from
* Pins C8 to C12
*
* Output is a 1 (no detection) 
* or a 0 (detection, non black object within range)
*/
uint8_t ReadIR(uint8_t);
