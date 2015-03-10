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
//HSI 2MHZ

uint16_t phase_ticks=0;
int16_t temp_error;

uint8_t switch_pressed_timer;

uint8_t temp_lvl;
uint8_t temp_lvl_real;

volatile uint8_t flags;

volatile uint8_t conv_num;
volatile uint16_t conv_result;

volatile uint8_t heat_counter;		//for caluclated heat||idle cycles
int8_t heat_cycles;			//pid regulated value


int8_t pgains[TEMP_LEVELS] = {1,1,1,1,2,2,2,2};
int8_t igains[TEMP_LEVELS] = {1,1,1,2,2,2,4,4};


pid_struct pid = {
    0, 0,		//dstate, istate
    10, 0,		//imax, imin
    50, 0,		//max/min output limits
    1, 1, 0		//p, i, d gains
};

uint16_t temp_adc[TEMP_LEVELS] = { \
    0,			\ //0 OFF
    180,		\ //1 200C
    220,		\ //2 250C
    260,		\ //3 300C
    300,		\ //4 350C
    340,		\ //5 400C
    390,		\ //6 450C
    450			\ //7 480C (MAX)
};


extern uint8_t txbuf[UART_BUF_SIZE];	//for debug


void mainLoop()
{

    while(1) {



	//pid processing and output debug msg
	if (get_flag(FLAG_END_ADC_CONV)) {

	    temp_error = temp_adc[temp_lvl_real] - conv_result;

	    if ( get_flag(FLAG_PREHEAT) && (temp_error<5) ) {			//check if preheat phase completed
		temp_lvl_real = temp_lvl;
		reset_flag(FLAG_PREHEAT);
	    }

	    if ( get_flag(FLAG_BLINK_ON) && ((get_flag(FLAG_PREHEAT))==0) ) {	//BLINK_OFF if temp stabilized
		if ( (temp_error>0) && (temp_error<5) ) {
		    LEDS_SET(temp_lvl);
		    reset_flag(FLAG_BLINK_ON);
		}
	    }

	    //calculate error for pid
	    temp_error = temp_adc[temp_lvl_real] - conv_result;
	    if (temp_error > 127) 
		temp_error=127;	// for int8_t in pid
	    else if (temp_error<-127)
		temp_error=-127;

	    heat_cycles = update_pid(&pid, (int8_t)(temp_error), conv_result);

	    reset_flag(FLAG_END_ADC_CONV);

//DBG
//	sprintf(txbuf,"%d,%d %d %d %x\r\n",conv_result,(uint16_t)(temp_lvl), (int16_t)heat_cycles, (int16_t)((int8_t)(temp_error)), (uint16_t)(flags));
//	UART_SendStr(txbuf);    //send result to uart
	}


	//zero-detection time-non-critical events processiong
	if (get_flag(FLAG_ZERO_REACHED)) {

	    reset_flag(FLAG_ZERO_REACHED);
	    phase_ticks++;


	    //leds blink
	    if (get_flag(FLAG_BLINK_ON)) {
		if ( (phase_ticks & 0b011111) == 0 ) {
		    LEDS_SET(temp_lvl);
		} else if ( (phase_ticks & 0b100000) == 0 ) {
		    LEDS_SET(0);
		}
	    }


	    //long switch-pressed: pwr-off
	    if (get_flag(FLAG_SWITCH_PRESSED)) {
		switch_pressed_timer++;
		if ( switch_pressed_timer == 0 ) {
		    temp_lvl=0;
		    temp_lvl_real=0;
		    LEDS_SET(0);
		}
	    }

	    //if key is pressed
	    if ( ((SWITCH_PORT->IDR & SWITCH_PIN)==0) && ((get_flag(FLAG_SWITCH_PRESSED))==0) ) {
		set_flag(FLAG_SWITCH_PRESSED);
		switch_pressed_timer=0;
		temp_lvl = (temp_lvl+1) % 8;
		LEDS_SET(temp_lvl);
		set_flag(FLAG_BLINK_ON);
		set_flag(FLAG_PREHEAT);

		pid.pgain=pgains[temp_lvl];
		pid.igain=igains[temp_lvl];

		if ((temp_lvl<7) && (temp_lvl>0)) {
		    temp_lvl_real = temp_lvl+1;
		} else {
		    reset_flag(FLAG_PREHEAT);
		    reset_flag(FLAG_BLINK_ON);
		    temp_lvl_real = temp_lvl;
		}

	    //if key is released (pull-up)
	    } else if ( (SWITCH_PORT->IDR & SWITCH_PIN) && get_flag(FLAG_SWITCH_PRESSED) ) {
		reset_flag(FLAG_SWITCH_PRESSED);
	    }


	}


    } // end while(1)

}






//zero-detection exti handler
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{

    set_flag(FLAG_ZERO_REACHED);	// for main-loop processing

    //zero-detection event processing
    if ( ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN ) {
        if ( get_flag(FLAG_END_TEMP_MEASURE) ) {
	    reset_flag(FLAG_END_TEMP_MEASURE);
	    if (heat_cycles) {
		HEATER_ON;
		set_flag(FLAG_HEATER_ENABLED);
		heat_counter = heat_cycles;
	    }
	} else if (heat_counter == 0) {
	    if (get_flag(FLAG_HEATER_ENABLED)) {
		HEATER_OFF;
		reset_flag(FLAG_HEATER_ENABLED);
		heat_counter = HEAT_IDLE_CYCLES; 
	    } 
	} else {
		heat_counter--;
	}
    } else if ( (ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN)==0 ) {
	if ( (heat_counter == 0) && (!get_flag(FLAG_HEATER_ENABLED)) ) {
	    //start ADC conversion
	    ZERO_DETECT_PORT->CR2 &= ~ZERO_DETECT_PIN;	//disable zero_detect_pin interrupt
	    conv_result=0;
	    conv_num=16;
	    ADC1->CR1 |= ADC1_CR1_ADON;			//start adc conversion
	}
    }

}


//end adc conversion
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
    ADC1->CSR &= ~ADC1_CSR_EOC;			//clear end-of-conversion flag

    conv_result += (ADC1->DRH << 8);		//add conversion to result
    conv_result += ADC1->DRL;

    if (conv_num) {				//if not all adc conversions: wait tim4 and start adc again
	conv_num--;
	TIM4->CR1 |= TIM4_CR1_CEN;		//enable tim4

    } else {					//all conversions finished

	conv_result=conv_result>>4;

	set_flag(FLAG_END_TEMP_MEASURE);
	set_flag(FLAG_END_ADC_CONV);

//	EXTI->CR1 |= (uint8_t)(EXTI_SENSITIVITY_RISE_FALL);	//set EXTI PORTS-sens
	ZERO_DETECT_PORT->CR2 |= ZERO_DETECT_PIN;	//enable zero_detect_pin interrupt
    }

}


//timer interrupt
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{

    TIM4->SR1 &= ~TIM4_SR1_UIF;	//clear update interrupt flag
    TIM4->CR1 &= ~TIM4_CR1_CEN;	//disable tim4
    ADC1->CR1 |= ADC1_CR1_ADON;	//start next adc conversion

}
