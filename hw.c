/*
Copyright (C) 2015 Alexander Sadakov <al.sadakov_dog_gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#include "main.h"


void GPIO_Config() {



    //zero detect pin config
    ZERO_DETECT_PORT->DDR &= ~ZERO_DETECT_PIN;	//in
    ZERO_DETECT_PORT->CR2 |= ZERO_DETECT_PIN;	//with_interrupt

    //switch pin config
    SWITCH_PORT->DDR &= ~SWITCH_PIN;		//in
    SWITCH_PORT->CR1 |= SWITCH_PIN;		//enable pull-up

    //exti config (zero detect && switch)
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);		//clear EXTI PORTA-sens interrupts
    EXTI->CR1 |= (uint8_t)(ZERO_DETECT_EXTI_RISE_FALL);	//set EXTI PORT-sense




    // led-display init (PP)
    LED_GPIO_PORT->DDR |= LED_GPIO_PINS;	//data direction
    LED_GPIO_PORT->CR1 |= LED_GPIO_PINS;	//pull-up/push-pull


    //heater pin config (PP)
    HEATER_PORT->DDR |= HEATER_PIN;	// out open-drain
//    HEATER_PORT->CR1 |= HEATER_PIN;
    HEATER_OFF;



}


void TIM4_Config() {
    TIM4->PSCR |= TIM4_PRESCALER_8;	//set timer prescaler
//    TIM4->ARR = 0xb0;			//set timer reload value (19ms for all adc conversions)
    TIM4->ARR = 0x90;			//set timer reload value (17ms for all adc conversions)
    TIM4->SR1 &= ~TIM4_SR1_UIF;		//clear update interrupt flag
    TIM4->IER |= TIM4_IT_UPDATE;		//enable interrupt
}


void ADC_Config()
{
    ADC1->CSR = ADC1_CSR_RESET_VALUE;	//reset CSR register
    ADC1->CSR |= TEMP_SENS_ADC_CHANNEL;	//set ADC input channel

    ADC1->CR1 |= ADC1_PRESSEL_FCPU_D18;	//set prescaler to fcpu/18

    ADC1->CR2 |= ADC1_CR2_ALIGN;	//set right data alignment (data in ADC_DRL register)

    ADC1->CR1 |= ADC1_CR1_ADON;		//enable adc

    ADC1->CSR |= ADC1_CSR_EOCIE;	//enable end-of-conversion interrupt

}








void HW_Init()
{

    disableInterrupts();

    GPIO_Config();
    ADC_Config();
    TIM4_Config();

    enableInterrupts();


}











