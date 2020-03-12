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
 //initializes GPIO Clock for Port A,B and C
 void GpioClockInit(void){
	 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
 }
 
 
 void led_IO_init (void)
{
    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN
        | RCC_APB2ENR_IOPAEN ;

    //Set the config and mode bits for Port C bit 9 and 8 so they will
    // be push-pull outputs (up to 50 MHz)
    GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8 ;
    GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8 ;
}

 void ConfigureLeds(void){
	 //configures PA9 to PA12 to general purpose output, LED output
	 GPIOA->CRH = 0x00033330;
 }
 
 
 uint16_t ReadDipSwitch(void){
	uint16_t sw1_val;
	 
	sw1_val = ((( GPIOA->IDR & ( GPIO_IDR_IDR6 | GPIO_IDR_IDR7)) >> 6) \
	| (( GPIOC->IDR & ( GPIO_IDR_IDR10 | GPIO_IDR_IDR11 )) >> 8)) \
	& 0x0F;
	 
	return (sw1_val);
 }
 
 uint16_t ReadDipSwitchPos1(void){
	uint16_t sw1_1;
	 
	sw1_1 = (( GPIOA->IDR & ( GPIO_IDR_IDR6)) >> 6) \
	& 0x01;
	 
	return (sw1_1);
 }
 
 uint16_t ReadDipSwitchPos2(void){
	uint16_t sw1_2;
	 
	sw1_2 = (( GPIOA->IDR & ( GPIO_IDR_IDR7)) >> 7) \
	& 0x01;
	 
	return (sw1_2);
 }
 
 uint16_t ReadDipSwitchPos3(void){
	uint16_t sw1_3;
	 
	sw1_3 = (( GPIOC->IDR & ( GPIO_IDR_IDR10)) >> 10) \
	& 0x01;
	 
	return (sw1_3);
 }
 uint16_t ReadDipSwitchPos4(void){
	uint16_t sw1_4;
	 
	sw1_4 = (( GPIOC->IDR & ( GPIO_IDR_IDR11)) >> 11) \
	& 0x01;
	 
	return (sw1_4);
 }
 
 uint16_t ReadRedButton(void){
	 uint16_t val;
	 
	val = (( GPIOB->IDR & ( GPIO_IDR_IDR8)) >> 8);
	 
	return (val);
 }

 
 uint16_t ReadBlackButton(void){
	 uint16_t val;
	 
	val = (( GPIOB->IDR & ( GPIO_IDR_IDR9)) >> 9);
	 
	return (val);
 }
 uint16_t ReadBlueButton(void){
	 uint16_t val;
	 
	val = (( GPIOC->IDR & ( GPIO_IDR_IDR12)) >> 12);
	 
	return (val);
 }
 uint16_t ReadGreenButton(void){
	 uint16_t val;
	 
	val = (( GPIOA->IDR & ( GPIO_IDR_IDR5)) >> 5);
	 
	return (val);
 }
 
  void UpdateLeds(uint16_t LED_val){
		uint16_t update_val;
		update_val = (LED_val<<9 & 0x1E00);
		uint16_t odrVal = GPIOA->ODR & 0xE1FF;
		GPIOA->ODR = odrVal | update_val;
 }
	
 void ButtonsUpdateLeds(void){
	 //read the button values
   uint16_t redButton = ReadRedButton();
	 uint16_t blackButton = ReadBlackButton();
	 uint16_t blueButton = ReadBlueButton();
	 uint16_t greenButton = ReadGreenButton();
	 //map outputs to led position
	 uint16_t ledValue = (redButton) | (blackButton << 1) | (blueButton << 2) | (greenButton << 3);
	 UpdateLeds(ledValue);
 }
 
 void Blink(void){
	 int delay = 600000;
	 UpdateLeds(~GPIOA->ODR);
	 Delay(delay);
 }
 
 uint16_t ReadIR(void){
	 return GPIOC->IDR & GPIO_IDR_IDR8;
	 
 }
 