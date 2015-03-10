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

#define get_flag(flagvar) (flags>>flagvar) & 1

//#define set_flag(flagvar) flags |= (1<<flagvar)
//#define reset_flag(flagvar) flags &= ~(1<<flagvar)
#define set_flag(flagvar) disableInterrupts(); flags |= (1<<flagvar); enableInterrupts()
#define reset_flag(flagvar) disableInterrupts(); flags &= ~(1<<flagvar); enableInterrupts()


#define CHECK_SWITCH_PERIOD 5
#define TEMP_LEVELS 8

#define HEAT_IDLE_CYCLES 10

typedef enum {
    FLAG_PREHEAT,
    FLAG_BLINK_ON,
    FLAG_ZERO_REACHED,
    FLAG_SWITCH_PRESSED,
    FLAG_HEATER_ENABLED,
    FLAG_END_TEMP_MEASURE,		//for processing in interrut
    FLAG_END_ADC_CONV			//for main-loop processing
} FLAGS;



void mainLoop(void);

extern INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6);
extern INTERRUPT_HANDLER(ADC1_IRQHandler, 22);
extern INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23);
