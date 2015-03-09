#include "main.h"

//HSI 2MHZ - default val(?)


//uint8_t check_switch_timer;
uint16_t phase_ticks=0;
uint8_t switch_pressed_timer;
int16_t temp_error;

uint8_t temp_lvl;
uint8_t temp_lvl_real;

volatile uint8_t flags;
extern volatile uint8_t heat_counter;
extern uint8_t txbuf[UART_BUF_SIZE];	//for debug
extern volatile uint16_t conv_result;

extern int8_t heat_cycles;		//pid regulated value
extern uint16_t temp_adc[TEMP_LEVELS];

int8_t pgains[TEMP_LEVELS] = {1,1,1,1,2,2,2,2};
int8_t igains[TEMP_LEVELS] = {1,1,1,2,2,2,4,4};

pid_struct pid = {
    0, 0,		//dstate, istate
//    3, -3,		//imax, imin
//    20, 0,		//imax, imin
    10, 0,		//imax, imin
    50, 0,		//pid output limits
//    1, 1, 2		//p, i, d gains
    1, 1, 0		//p, i, d gains
};




static void delay(uint32_t t)
{
  while(t--);
}



int main( void )
{
    uint8_t i=0;

    disableInterrupts();

    GPIO_Config();
    UART_Config();
    ADC_Config();

    flags=0;
    temp_lvl=0;
    LEDS_OFF;

    heat_counter = HEAT_IDLE_CYCLES;
//    check_switch_timer=CHECK_SWITCH_PERIOD;

    enableInterrupts();

    UART_SendStr("OK!\r\n");

//    set_flag(FLAG_BLINK_ON);

    while(1) {
//	delay(20000);
//	delay(2000);
	//UART1_SendData8('!');
//	printf_tiny("Ok\r\n");
//	printf("%c\n\r", 'p');



    //pid processing and output debug msg
    if (get_flag(FLAG_END_ADC_CONV)) {

	temp_error = temp_adc[temp_lvl_real] - conv_result;
//	if (temp_error > 127) 
//	    temp_error=127;	// for int8_t in pid
//disableInterrupts();
	if ( get_flag(FLAG_PREHEAT) && (temp_error<5) ) {
	    temp_lvl_real = temp_lvl;
	    reset_flag(FLAG_PREHEAT);
	}
/*
//	if ( get_flag(FLAG_BLINK_ON) && (!get_flag(FLAG_PREHEAT)) && (temp_error<5) ) {
if (!get_flag(FLAG_PREHEAT)) {
	if ( get_flag(FLAG_BLINK_ON) && (temp_error<5) ) {
//	if ( get_flag(FLAG_BLINK_ON) && (temp_adc[temp_lvl] - conv_result) ) {
	    reset_flag(FLAG_BLINK_ON);
	    LEDS_SET(temp_lvl);
	}
}
*/
//	if ( get_flag(FLAG_BLINK_ON) && ((get_flag(FLAG_PREHEAT))==0) && (temp_error<5) ) {
	if ( get_flag(FLAG_BLINK_ON) && ((get_flag(FLAG_PREHEAT))==0) ) {
	    if ( (temp_error>0) && (temp_error<5) ) {
		LEDS_SET(temp_lvl);
		reset_flag(FLAG_BLINK_ON);
	    }
	}


//enableInterrupts();

//	temp_error = temp_adc[temp_lvl] - conv_result;
	temp_error = temp_adc[temp_lvl_real] - conv_result;
//	temp_error =  conv_result - temp_adc[temp_lvl];
	if (temp_error > 127) 
	    temp_error=127;	// for int8_t in pid
	else if (temp_error<-127)
	    temp_error=-127;
/*
	if ( (temp_error<3) && get_flag(FLAG_PREHEAT) ) {
	    temp_lvl_real = temp_lvl;
	    reset_flag(FLAG_PREHEAT);
	}
*/
	heat_cycles = update_pid(&pid, (int8_t)(temp_error), conv_result);

//	heat_cycles = update_pid(&pid, (int8_t)(temp_adc[temp_lvl_real] - conv_result), conv_result);
	reset_flag(FLAG_END_ADC_CONV);
//	sprintf(txbuf,"%d,%d %d %d:%d e %d \r\n",conv_result,(uint16_t)(temp_lvl), (int16_t)heat_cycles, (int16_t)(pid.dstate),(int16_t)(pid.istate), (int16_t)((int8_t)(temp_error)));
//!	sprintf(txbuf,"%d,%d %d %d %x\r\n",conv_result,(uint16_t)(temp_lvl), (int16_t)heat_cycles, (int16_t)((int8_t)(temp_error)), (uint16_t)(flags));
//!	UART_SendStr(txbuf);	//send result to uart


    }


//    //switch event processing
//    if (get_flag(FLAG_SWITCH_EVENT)) {

    //zero-detection time-non-critical events processiong
    if (get_flag(FLAG_ZERO_REACHED)) {

	reset_flag(FLAG_ZERO_REACHED);
	phase_ticks++;
/*
	if (i==0) {
	    i=3;
	    sprintf(txbuf,"%d %d\r\n",(uint16_t)(temp_lvl),(uint16_t)(SWITCH_PORT->IDR & SWITCH_PIN));
	    UART_SendStr(txbuf);	//send result to uart
	}
	i--;
*/
	//leds blink
	if (get_flag(FLAG_BLINK_ON)) {
	    if ( (phase_ticks & 0b011111) == 0 ) {
		LEDS_SET(temp_lvl);
	    } else if ( (phase_ticks & 0b100000) == 0 ) {
		LEDS_SET(0);
	    }
	}


	//long switch-pressed
	if (get_flag(FLAG_SWITCH_PRESSED)) {
	    switch_pressed_timer++;
	    if ( switch_pressed_timer == 0 ) {
		temp_lvl=0;
		temp_lvl_real=0;
		LEDS_SET(0);
	    }
	}

//	if (check_switch_timer == 0) {
//	    check_switch_timer=CHECK_SWITCH_PERIOD;
//	}

	if ( ((SWITCH_PORT->IDR & SWITCH_PIN)==0) && ((get_flag(FLAG_SWITCH_PRESSED))==0) ) {	//if key is pressed
//	    UART1->DR = '_';
	    set_flag(FLAG_SWITCH_PRESSED);
//	    set_flag(FLAG_SWITCH_PRESSED | FLAG_PREHEAT);
	    switch_pressed_timer=0;
	    temp_lvl = (temp_lvl+1) % 8;
	    LEDS_SET(temp_lvl);
	    set_flag(FLAG_BLINK_ON);
	    set_flag(FLAG_PREHEAT);

	    pid.pgain=pgains[temp_lvl];
	    pid.igain=igains[temp_lvl];

	    if ((temp_lvl<7) && (temp_lvl>0)) {
//		set_flag(FLAG_PREHEAT);
		temp_lvl_real = temp_lvl+1;
	    } else {
		reset_flag(FLAG_PREHEAT);
		reset_flag(FLAG_BLINK_ON);
		temp_lvl_real = temp_lvl;
	    }

	} else if ( (SWITCH_PORT->IDR & SWITCH_PIN) && get_flag(FLAG_SWITCH_PRESSED) ) {			//if key is released (pull-up)
//	    UART1->DR = '=';
	    reset_flag(FLAG_SWITCH_PRESSED);
//	} else if ( ((SWITCH_PORT->IDR & SWITCH_PIN) == 0) && !get_flag(FLAG_SWITCH_PRESSED) ) {	//if key is pressed
	}

//	check_switch_timer--;

    }

//    printf("%d\r\n",q);

//	GPIOD->ODR ^= GPIO_PIN_3;
//	GPIOD->ODR &= ~GPIO_PIN_3;
//	LEDS_SET(temp_lvl);
/*
//	LED_GPIO_PORT->ODR ^= (i<<3);
	LEDS_SET(i);
	i = (i+1) % 8;


	delay(20000);
//	GPIOD->ODR ^= GPIO_PIN_3;
//	GPIOD->ODR |= GPIO_PIN_3;

//	LED_GPIO_PORT->ODR &= LED_GPIO_MASK;
	LEDS_OFF;
*/
/*
	GPIOD->ODR ^= GPIO_PIN_3;

	delay(5000);
	GPIOD->ODR ^= GPIO_PIN_3;
	delay(5000);
	GPIOD->ODR ^= GPIO_PIN_3;
*/

    }
}




