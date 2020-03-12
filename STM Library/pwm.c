/******************************************************************************
 * Name:    pwm.c
 * Description: PWM functions
 * Version: V1.00
 * Authors: Avery Cameron
 *
 *****************************************************************************/
#include "stm32f10x.h"
void PwmInit(uint16_t period, uint16_t pulswidth){
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
	//0.1 ms 
	TIM1->PSC = 0x095f;
	//100 counts 10 ms
	TIM1->ARR = period;
	//50 counts 5 ms
	TIM1->CCR1 = pulswidth;
	//main output enable, force idle level first
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	//enable timer 1
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
}

void setDutyCycle(uint16_t pulswidth) {
	TIM1->CCR1 = pulswidth;
	//Reinit the counter
	TIM1->EGR |= TIM_EGR_UG;
}