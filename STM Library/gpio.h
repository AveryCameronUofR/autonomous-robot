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
 
 //reads the total dipswitch value
 uint16_t ReadDipSwitch(void);
 //reads the first position of the dipswitch
 uint16_t ReadDipSwitchPos1(void);
 //reads the second position of the dipswitch
 uint16_t ReadDipSwitchPos2(void);
 //reads the third position of the dipswitch
 uint16_t ReadDipSwitchPos3(void);
 //reads the fourth position of the dipswitch
 uint16_t ReadDipSwitchPos4(void);
 
 //reads the red button value
 uint16_t ReadRedButton(void);
 //reads the black button value
 uint16_t ReadBlackButton(void);
 //reads the black button value
 uint16_t ReadBlueButton(void);
 //reads the black button value
 uint16_t ReadGreenButton(void);
 
 //Updates leds based on given value
 void UpdateLeds(uint16_t);
 //Buttons update the leds directly
 void ButtonsUpdateLeds(void);
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
 