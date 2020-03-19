/******************************************************************************
* Name:    lcd.h
* Description: STM32 LCD functions for HITACHI 44780 compatible controllers
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
	
#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2
	
// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002
#define LCD_CM_DIS 0x00230000
#define LCD_DM_ENA 0x00200003
#define LCD_DM_DIS 0x00220001
	
//Initializes LCD with 8 bit display
void LcdInit(void);
//initializes clocks for port b and c
void LcdClockInit(void);
//Configures the LCD pins as output
void ConfigureLcdPins(void);
//sends a command to the LCD 
void CommandToLcd(uint8_t data);

//sends data to the LCD 
void DataToLcd(uint8_t data);
//prints string to LCD
void PrintStringToLcd(char str[]);
void PrintHexToLcd(uint16_t data);
//clears LCD 
void LcdClear(void);
void LcdFirstLine(void);
void LcdSecondLine(void);
void LcdSetCursor(uint8_t data);
void reg_out( uint16_t reg_data);
