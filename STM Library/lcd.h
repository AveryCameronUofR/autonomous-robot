/******************************************************************************
* Name:    lcd.h
* Description: STM32 LCD functions for HITACHI 44780 compatible controllers
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
	
#define LCD_8B2L 0x38 // Enable 8 bit data, 2 display lines
#define LCD_DCB  0x0F // Enable Display, Cursor, Blink
#define LCD_MCR  0x06 // Set Move Cursor Right
#define LCD_CLR  0x01 // Home and clear LCD
#define LCD_LN1  0x80 // Set DDRAM to start of line 1
#define LCD_LN2  0xC0 // Set DDRAM to start of line 2
	
// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002
#define LCD_CM_DIS 0x00230000
#define LCD_DM_ENA 0x00200003
#define LCD_DM_DIS 0x00220001
	
/**
* Name: LcdInit
* Input: None
* Return: None
*
* Initializes the LCD Clock and pins and LCD as a 8 bit controller
* Sets the display and cursor on and cursor to blink
* Sets entry mode to increment not shift 
*/
void LcdInit(void);

/**
* Name: LcdClockInit
* Input: None
* Return: None
*
* Initializes the LCD Clocks for GPIOB and C
*/
void LcdClockInit(void);

/**
* Name: ConfigureLcdPins
* Input: None
* Return: None
*
* Configures LCD Pins PB0,1,5 and PC0-7 as General Purpose Output
*/
void ConfigureLcdPins(void);


/**
* Name: CommandToLcd
* Input: 
* 	uint8_t data: Command to send to LCD in Command Mode 
* Return: None
*
* Sets LCD to command mode and sends input data to the LCD 
*/
void CommandToLcd(uint8_t data);

/**
* Name: DataToLcd
* Input: 
* 	uint8_t data: Data to send to LCD
* Return: None
*
* Sets LCD to Data mode and sends input data to the LCD 
*/
void DataToLcd(uint8_t data);


/**
* Name: PrintStringToLcd
* Input: 
* 	char str[] string to print to LCD
* Return: NONE
* NOTE:Outputs the string to the LCD
*
* Prints string to the LCD char by char
*/
void PrintStringToLcd(char str[]);

/**
* Name: PrintHexToLcd
* Input: 
* 	uint16_t data: Hex Value to print to the screen
* Return: NONE
* NOTE: Outputs the Hex value with ASCII characters to the LCD 
*
* Prints HEX to the LCD converting value to ASCII
*/
void PrintHexToLcd(uint16_t data);

/**
* Name: LcdClear
* Input: NONE
* Return: NONE
*
* Sends Clear Command to the LCD and clears the Screen
*/
void LcdClear(void);

/**
* Name: LcdFirstLine
* Input: NONE
* Return: NONE
*
* Sets LCD Cursor to the first position of the first line
*/
void LcdFirstLine(void);

/**
* Name: LcdSecondLine
* Input: NONE
* Return: NONE
*
* Sets LCD Cursor to the first position of the second line
*/
void LcdSecondLine(void);

/**
* Name: LcdSetCursor
* Input: 
*		uint8_t data: position of the cursor
* Return: NONE
*
* Sets LCD Cursor to the given position
* Note: 
* 0x02 is first line, first position
* 0xC0 is second line, first position
*/
void LcdSetCursor(uint8_t data);

/**
* Name: OutputRegisterValue
* Input: 
*		uint16_t reg_data: register data to output
* Return: NONE
*
* Prints given Register value to the LCD Screen
*/
void OutputRegisterValue( uint16_t reg_data);
