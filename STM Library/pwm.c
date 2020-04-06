/******************************************************************************
* Name:    pwm.c
* Description: PWM functions
* Version: V1.00
* Authors: Avery Cameron
*
*****************************************************************************/
#include "stm32f10x.h"
void Tim1Ch1PwmInit(uint16_t period, uint16_t pulsewidth){
	//Enable GPIOA and AFIO
	RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_TIM1EN;
	//set PA8 to AF Output
	GPIOA->CRH = 0xB;
	
	//enable timer 1
	TIM1->CR1 |= TIM_CR1_CEN;
	//output idle state oc1 = 1 when moe = 0
	TIM1->CR2 |= TIM_CR2_OIS1;
	//Reinit the counter
	TIM1->EGR |= TIM_EGR_UG;
	//pwm mode 1, preload enable, fast enable
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	//enable ch1 output on pa8
	TIM1->CCER |= TIM_CCER_CC1E;
	//0.05 ms 
	TIM1->PSC = 0x04Af;
	//200 counts 20 ms
	TIM1->ARR = period;
	//50 counts 5 ms
	TIM1->CCR1 = pulsewidth;
	//main output enable, force idle level first
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	//enable timer 1
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void Tim4PwmInit(uint16_t period, uint16_t pulsewidth){
	//Enable GPIOB and AFIO
	RCC->APB2ENR |=  RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
	
	//Enable Tim 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//set PB6-9 to AF Output
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0xBB000000;
	GPIOB->CRH &= 0xFFFFFF00;
	GPIOB->CRH |= 0x000000BB;
	//enable timer 4
	TIM4->CR1 |= TIM_CR1_CEN;
	//output idle state oc1 = 1 when moe = 0 for the channels
	TIM4->CR2 |= TIM_CR2_OIS1;
	TIM4->CR2 |= TIM_CR2_OIS2;
	TIM4->CR2 |= TIM_CR2_OIS3;
	TIM4->CR2 |= TIM_CR2_OIS4;
	
	//Reinit the counter
	TIM4->EGR |= TIM_EGR_UG;

	//Set pwm mode 1, preload enable, fast enable for the channels
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE;
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC4FE;
	
	//enable ch1-4 output on PB6-9
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCER |= TIM_CCER_CC2E;
	TIM4->CCER |= TIM_CCER_CC3E;
	TIM4->CCER |= TIM_CCER_CC4E;
	
	TIM4->PSC = 0x04Af;
	TIM4->ARR = period;
	TIM4->CCR1 = pulsewidth;
	TIM4->CCR2 = pulsewidth;
	TIM4->CCR3 = pulsewidth;
	TIM4->CCR4 = pulsewidth;
	
	//main output enable, force idle level first
	TIM4->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	//Enable Timer 4
	TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void motor_clock(void)
{
	RCC->APB2ENR |=RCC_APB2ENR_IOPBEN; //clock enable for portB
		 
	GPIOB->CRL |= GPIO_CRL_MODE3 | GPIO_CRL_MODE4;
	GPIOB->CRL &= ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4;
	
	GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15;
	GPIOB->CRH &= ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12 & ~GPIO_CRH_CNF13 & ~GPIO_CRH_CNF14 & ~GPIO_CRH_CNF15;
}

void SetTim1DutyCycle(uint16_t pulsewidth) {
	TIM1->CCR1 = pulsewidth;
	//Reinit the counter
	TIM1->EGR |= TIM_EGR_UG;
}

void SetTim4DutyCycle(uint16_t pulsewidth) {
	TIM4->CCR1 = pulsewidth;
	TIM4->CCR2 = pulsewidth;
	TIM4->CCR3 = pulsewidth;
	TIM4->CCR4 = pulsewidth;
	//Reinit the counter
	TIM4->EGR |= TIM_EGR_UG;
}
