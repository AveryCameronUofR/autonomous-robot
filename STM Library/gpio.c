/******************************************************************************
 * Name:    gpio.h
 * Description: STM32 gpio functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
#include "gpio.h"
#include "clock.h"
#include "pwm.h"
void GpioClockInit(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
}

void ConfigureLeds(void){
	//configures PA9 to PA12 to general purpose output, LED output
	GPIOA->CRH &= 0xFFF0000F;
	GPIOA->CRH |= 0x00033330;
	GPIOA->BSRR = 0x00001E00;
}

void UpdateLeds(uint16_t LED_val){
	uint16_t update_val;
	//update the value in PA9-12 (inverse logic requires the 0xE1FF)
	update_val = (LED_val<<9 & 0x1E00);
	uint16_t odrVal = GPIOA->ODR & 0xE1FF;
	GPIOA->ODR = odrVal | update_val;
}

void BlinkLeds(void){
	int delay = 600000;
	UpdateLeds(~GPIOA->ODR);
	Delay(delay);
}

void ConfigureSwitches(){
	GPIOA->CRL &= 0xFFF00FFF;
	GPIOA->CRL |= 0x00088000;
	GPIOA->BSRR = 0x00000018;
}

uint8_t ReadSwitches(){
	uint8_t switch1 = ((GPIOA->IDR & GPIO_IDR_IDR3) >> 3) & 1;
	uint8_t switch2 = ((GPIOA->IDR & GPIO_IDR_IDR4) >> 4) & 1;
	if (switch1 == 0 || switch2 == 0){
		return 1;
	}
	return 0;
}

void ConfigureIrSensors(){
	GPIOA->CRL &= 0xFF0FFFFF;
	GPIOA->CRL |= 0x00400000;
	GPIOC->CRL &= 0xFFFFFFF0;
	GPIOC->CRL |= 0x00000004;
}

uint8_t ReadIR(uint8_t sensor){
	if (sensor == 1){
		return (GPIOA->IDR & (1 << (5))) >> (5) & 0x1;
	}
	return (GPIOC->IDR & (1 << (8))) >> (8) & 0x1;
}

void ConfigureMotorInputs(){
	//JTAG-DP Disabled and SW-DP Enabled
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	
	//Configure GPIO Output
	GPIOB->CRL |= GPIO_CRL_MODE3 | GPIO_CRL_MODE4;
	GPIOB->CRL &= ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4;
	
	GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15;
	GPIOB->CRH &= ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12 & ~GPIO_CRH_CNF13 & ~GPIO_CRH_CNF14 & ~GPIO_CRH_CNF15;
}

void MoveForward(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR3;
	GPIOB->ODR &= ~GPIO_ODR_ODR4;
	
	GPIOB->ODR |= GPIO_ODR_ODR10;
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	
	GPIOB->ODR |= GPIO_ODR_ODR12;
	GPIOB->ODR &= ~GPIO_ODR_ODR13;
	
	GPIOB->ODR |= GPIO_ODR_ODR14;
	GPIOB->ODR &= ~GPIO_ODR_ODR15;
}

void MoveBackward(void)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR3;
	GPIOB->ODR |= GPIO_ODR_ODR4;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR10;
	GPIOB->ODR |= GPIO_ODR_ODR11;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR12;
	GPIOB->ODR |= GPIO_ODR_ODR13;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR14;
	GPIOB->ODR |= GPIO_ODR_ODR15;
}

void TurnLeft(void)
{
	GPIOB->ODR |= GPIO_ODR_ODR3;
	GPIOB->ODR &= ~GPIO_ODR_ODR4;
	
	GPIOB->ODR |= GPIO_ODR_ODR10;
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR12;
	GPIOB->ODR |= GPIO_ODR_ODR13;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR14;
	GPIOB->ODR |= GPIO_ODR_ODR15;
}


void TurnRight(void)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR3;
	GPIOB->ODR |= GPIO_ODR_ODR4;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR10;
	GPIOB->ODR |= GPIO_ODR_ODR11;
	
	GPIOB->ODR |= GPIO_ODR_ODR12;
	GPIOB->ODR &= ~GPIO_ODR_ODR13;
	
	GPIOB->ODR |= GPIO_ODR_ODR14;
	GPIOB->ODR &= ~GPIO_ODR_ODR15;
}

void Stop(uint16_t pulsewidth)
{
	for (int i = pulsewidth; i > 0; i-=5){
		SetTim4DutyCycle(i);
	}
	GPIOB->ODR &= ~GPIO_ODR_ODR3;
	GPIOB->ODR &= ~GPIO_ODR_ODR4;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR10;
	GPIOB->ODR &= ~GPIO_ODR_ODR11;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR12;
	GPIOB->ODR &= ~GPIO_ODR_ODR13;
	
	GPIOB->ODR &= ~GPIO_ODR_ODR14;
	GPIOB->ODR &= ~GPIO_ODR_ODR15;
}

void Start(uint16_t pulsewidth)
{
	for (int i = 0; i < pulsewidth; i+=5){
		SetTim4DutyCycle(i);
	}
}
