/******************************************************************************
 * Name:    gpio.h
 * Description: STM32 gpio functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
/**
* Name: GpioClockInit
* Input: None
* Return: None
*
* Initializes clocks for GPIO A, B and C
*/
void GpioClockInit(void);


/**
* Name: ConfigureLeds
* Input: None
* Return: None
*
* Configures Onboard LEDs for general purpose push pull output
* Initializes pins PA9-12 as GP output 
*/
void ConfigureLeds(void);

/**
* Name: UpdateLeds
* Input: uint16_t Register value to update LEDs with
* Return: None
*
* Shifts the given value left 9. ANDs it with 0x1E00 to only change the LEDs
* Applies the updated value
*
* Note: 1 in the input is an ON indicator for the LED
*/
void UpdateLeds(uint16_t);

/**
* Name: BlinkLeds
* Input: None
* Return: None
*
* Turns ON or OFF the LEDs on pins PA9-12 for 1 sec
* Note: Changes current state, will have to be looped for desired blink count
*/
void BlinkLeds(void);

/**
* Name: ConfigureIrSensors
* Input: None
* Output: None
*
* Sets up IR Sensors on pins PC8 to 12 as general Input
*/
void ConfigureIrSensors(void);

/**
* Name: ReadIR
* Input: IR Sensor to detect
* Return: IR Sensor Output
*
* Input is a number from 1 to 5 
* for the 5 IR Sensors on the board from
* Pins C8 to C12
*
* Output is a 1 (no detection) 
* or a 0 (detection, non black object within range)
*/
uint8_t ReadIR(uint8_t);


/**
* Name: ConfigureMotorInputs
* Input: None
* Output: None
*
* Configures Pins PB 3,4,10 to 15 as GP output 
* These pins are used for motor control as follows:
* PB3 Front Right
* PB4 Front Right
* PB10 Front Left
* PB11 Front Left
* PB12 Rear Right
* PB13 Rear Right
* PB14 Rear Left
* PB15 Rear Left
*/
void ConfigureMotorInputs(void);
