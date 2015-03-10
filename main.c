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



extern volatile uint8_t flags;
extern uint8_t temp_lvl;
extern volatile uint8_t heat_counter;
extern int8_t heat_cycles;

extern uint8_t txbuf[UART_BUF_SIZE];	//for debug



int main( void )
{
    uint8_t i=0;

    disableInterrupts();

    HW_Init();
    UART_Config();

    enableInterrupts();


    flags=0;
    temp_lvl=0;
    LEDS_OFF;

    heat_counter = HEAT_IDLE_CYCLES;
    heat_cycles=30;


    UART_SendStr("OK!\r\n");


    mainLoop();

    return 0;

}




