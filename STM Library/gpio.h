/******************************************************************************
 * Name:    gpio.h
 * Description: STM32 gpio functions
 * Version: V1.00
 * Authors: Avery Cameron Raymond Knorr
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
* Input: uint16_t LED_val: Register value to update LEDs with
* Return: None
*
* Shifts the given value left 9. ANDs it with 0x1E00 to only change the LEDs
* Applies the updated value
*
* Note: 1 in the input is an ON indicator for the LED
*/
void UpdateLeds(uint16_t LED_val);

/**
* Name: ConfigureSwitches
* Input: None
* Output: None
*
* Sets up Switches on pins PA3 and 4 as as push/pull input
*/
void ConfigureSwitches(void);

/**
* Name: ReadSwitches
* Input: None
* Output: Output of switches or'd together
*
* Reads Switches on pins PA3 and 4 and combines the result, if either is pressed, 1 is returned
*/
uint8_t ReadSwitches();

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
* Input: 
* 	sensor: IR Sensor number to detect
* Return: IR Sensor Output
*
* Input is a number from 1 to 5 
* for the 5 IR Sensors on the board from
* Pins C8 to C12
*
* Output is a 1 (no detection) 
* or a 0 (detection, non black object within range)
*/
uint8_t ReadIR(uint8_t sensor);


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


/**
* Name: MoveForward
* Input: None
* Output: None
*
* Turns on motors pins PB3, PB10, PB12, and PB 14 
* and off PB4, PB11, PB13, and PB15 to set the motors forward.
* IN1, IN3 of motor controller 1 and 2 (PB3,PB10,PB12,PB14) are on
* And IN2 and IN4 are off. 
*/
void MoveForward(void);

/**
* Name: MoveBackward
* Input: None
* Output: None
*
* Turns on motors pins PB4, PB11, PB13, and PB 15
* and off PB0, PB10, PB12, and PB14
* IN2 and 4 on, IN 1 and 3 off
*/
void MoveBackward(void);

/**
* Name: TurnRight
* Input: None
* Output: None
*
* Turns on motors pins PB3, PB10, PB13, and PB 15 
* and off PB4, PB11, PB12, and PB14
* Turn the Left side motors forward and right side backwards.
*/
void TurnRight(void);

/**
* Name: TurnLeft
* Input: None
* Output: None
*
* Turns on motors pins PB4, PB11, PB12, and PB 14
* and off PB0, PB10, PB13, and PB15
* Turn the Right side motors forward and Left side backwards.
*/
void TurnLeft(void);

/**
* Name: Stop
* Input: current pulsewidth 
* Output: None
*
* Turns off motors pins PB4, PB11, PB12, and PB 14
* and PB0, PB10, PB13, and PB15
*/
void Stop(uint16_t pulsewidth);

/**
* Name: Start
* Input: current pulsewidth 
* Output: None
*
* Updates the pulsewidth gradually
*/
void Start(uint16_t pulsewidth);