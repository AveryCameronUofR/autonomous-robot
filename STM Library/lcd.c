/******************************************************************************
* Name:    lcd.c
* Description: STM32 LCD functions for HITACHI 44780 compatible controllers
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
#include "clock.h"
#include "lcd.h"
#include <string.h>

void LcdInit(void){
	LcdClockInit();
	ConfigureLcdPins();
	//poll controller
	CommandToLcd(LCD_8B2L);
	CommandToLcd(LCD_8B2L);
	CommandToLcd(LCD_8B2L);

	CommandToLcd(LCD_8B2L);
	
	CommandToLcd(LCD_DCB);
	CommandToLcd(LCD_CLR);
	
	CommandToLcd(LCD_MCR);
}

//initializes LCD Clock for Port B and C
//Called by Clock Init
void LcdClockInit(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
}

void ConfigureLcdPins(void){
	//configures PB0,1, 5 to general purpose output
	GPIOB->CRL &= 0xFF0FFF00;
	GPIOB->CRL |= 0x00300033;
	
	//configures PC0-7 to general purpose output
	GPIOC->CRL |= 0x33333333;
}

void LcdClear(void){
	CommandToLcd(LCD_CLR);
}

void LcdFirstLine(void){
	CommandToLcd(0x02);
}
void LcdSecondLine(void){
 CommandToLcd(0xC0);
}

void LcdSetCursor(uint8_t data){
	CommandToLcd(0x80 | data);
}

void CommandToLcd(uint8_t data){
	//Sets RS low(0, takes a command), Write on (0), enable high
	GPIOB->BSRR=LCD_CM_ENA;
	GPIOC->ODR &= 0xFF00;
	GPIOC->ODR |= data;
	Delay(80000);
	//Sets RS low(0, takes a command), R/W low (0 is write), enable low
	GPIOB->BSRR = LCD_CM_DIS;
	Delay(800000);
}

void DataToLcd(uint8_t data){
	//Sets RS high(1, sends data), Write on (0), enable high
	GPIOB->BSRR=LCD_DM_ENA;
	GPIOC->ODR &= 0xFF00;
	GPIOC->ODR |= data;
	Delay(8000);
	//enable low
	GPIOB->BSRR = LCD_DM_DIS;
	Delay(80000);
}
void PrintStringToLcd(char str[]){
	for(int i = 0; i < strlen(str); i++){
		DataToLcd(str[i]);
	} 
}
void PrintHexToLcd(uint16_t data){
	//converts to ASCII Value (Numbers vs letters)
	if (data <= 0x09){
		DataToLcd(data + 0x30);
	} 
	if (data > 0x09){
		DataToLcd(data + 0x37);
	}
}

void OutputRegisterValue(uint16_t reg_data){
	int i;
	uint16_t shifted_val;
	for (i=16; i >= 0 ; i = (i-4))
	{
		shifted_val = (reg_data >> i) & 0xf;
		PrintHexToLcd(shifted_val);
	}
}
