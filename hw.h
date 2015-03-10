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

//
//ZERO-DETECTION PIN - EXTI RISE/FALL
//
#define ZERO_DETECT_PORT GPIOD
#define ZERO_DETECT_PIN GPIO_PIN_3
//#define ZERO_DETECT_EXTI EXTI_PORT_GPIOD
#define ZERO_DETECT_EXTI_RISE_FALL 0b11000000	//zero-detect-port exti sensitivity (write to CR1)


//
//SWITCH PIN - INPUT
//
#define SWITCH_PORT GPIOC
#define SWITCH_PIN GPIO_PIN_6


//
//LED-PANEL - PUSH-PULL
//
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_PINS GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
#define LED_GPIO_MASK  0b11000111

#define LEDS_OFF LED_GPIO_PORT->ODR &= LED_GPIO_MASK;
#define LEDS_SET(val) LED_GPIO_PORT->ODR &= LED_GPIO_MASK; LED_GPIO_PORT->ODR ^= (val<<3);


//
//HEATER - PUSH-PULL
//
#define HEATER_PORT GPIOD
#define HEATER_PIN GPIO_PIN_4

#define HEATER_ON HEATER_PORT->ODR &= ~HEATER_PIN
#define HEATER_OFF HEATER_PORT->ODR |= HEATER_PIN


//
//TEMP SENSOR - ADC
//
#define TEMP_SENS_ADC_CHANNEL ADC1_CHANNEL_3



void HW_Init(void);
