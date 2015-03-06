#include "main.h"

extern volatile uint8_t flags;
//extern uint8_t temp_lvl;

//extern uint8_t check_switch_timer;

void GPIO_Config() {
/*
    //debug led init
    GPIOD->DDR |= GPIO_PIN_3;	//data direction
    GPIOD->CR1 |= GPIO_PIN_3;	//pull-up/push-pull
//    GPIOD->ODR |= GPIO_PIN_3;
//    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
*/



    //zero detect pin config
    ZERO_DETECT_PORT->DDR &= ~ZERO_DETECT_PIN;	//in
    ZERO_DETECT_PORT->CR2 |= ZERO_DETECT_PIN;	//with_interrupt

    //switch pin config
    SWITCH_PORT->DDR &= ~SWITCH_PIN;		//in
    SWITCH_PORT->CR1 |= SWITCH_PIN;		//enable pull-up
//    SWITCH_PORT->CR2 |= SWITCH_PIN;		//with_interrupt


    //exti config (zero detect && switch)
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);		//clear EXTI PORTA-sens interrupts
//    EXTI->CR1 |= (uint8_t)(EXTI_SENSITIVITY_RISE_FALL);	//set EXTI PORTS-sens
//    EXTI->CR1 |= (uint8_t)(EXTI_SENSITIVITY_RISE_ONLY);	//set EXTI PORTS-sens
//    EXTI->CR1 |= (uint8_t)(ZERO_DETECT_EXTI_RISE_FALL | SWITCH_EXTI_RISE_FALL);	//set EXTI PORT-sense
    EXTI->CR1 |= (uint8_t)(ZERO_DETECT_EXTI_RISE_FALL);	//set EXTI PORT-sense





    // led-display init (PP)
    LED_GPIO_PORT->DDR |= LED_GPIO_PINS;	//data direction
    LED_GPIO_PORT->CR1 |= LED_GPIO_PINS;	//pull-up/push-pull


    //heater pin config (PP)
    HEATER_PORT->DDR |= HEATER_PIN;	// out open-drain
//    HEATER_PORT->CR1 |= HEATER_PIN;
    HEATER_OFF;




//    enableInterrupts();

}








INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{

/*
//ZERO_DETECT_PORT->CR2 &= ~ZERO_DETECT_PIN;	//with_interrupt

    if ( ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN ) {
//	STATUS_LED_ON;
	ADC_StartConversion();
//    } else if ( (GPIO_ReadInputData(ZERO_DETECT_PORT) & ZERO_DETECT_PIN)==0 ) {
    } else if ( (ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN)==0 ) {
//ZERO_DETECT_PORT->CR2 &= ~ZERO_DETECT_PIN;	//with_interrupt
//	GPIOD->ODR &= ~GPIO_PIN_3;	//STATUS_LED_OFF
    }
*/
}

INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
//  if ((GPIO_ReadInputData(JOYSTICK_PORT) & JOYSTICK_LEFT_PIN) == 0x00)
//  {
//    GPIO_WriteReverse(LEDS_PORT, LED1_PIN);
//  }
}

//switch-press-release exti handler
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
/*
    if ( SWITCH_PORT->IDR & SWITCH_PIN ) {
	HEATER_ON;
//	UART_SendStr("+");
    } else if ( (SWITCH_PORT->IDR & SWITCH_PIN) == 0 ) {
	HEATER_OFF;
//	UART_SendStr("-");
    }
*/
}


//zero-detection exti handler
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
/*
    //KEY CHECK
//    if ( SWITCH_PORT->IDR & SWITCH_PIN ) {			//if key is not pressed (pull-up)
    if ( (SWITCH_PORT->IDR & SWITCH_PIN) && get_flag(FLAG_SWITCH_PRESSED) ) {			//if key is released (pull-up)
//	HEATER_ON;
//	UART_SendStr("+");
	reset_flag(FLAG_SWITCH_PRESSED);
//    } else if ( (SWITCH_PORT->IDR & SWITCH_PIN) == 0 ) {	//if key is pressed
    } else if ( ((SWITCH_PORT->IDR & SWITCH_PIN) == 0) && !get_flag(FLAG_SWITCH_PRESSED) ) {	//if key is pressed
//	HEATER_OFF;
//	UART_SendStr("-");
	set_flag(FLAG_SWITCH_PRESSED);
	temp_lvl = (temp_lvl+1) % 8;
	LEDS_SET(temp_lvl);
    }
*/

//switch-event processing
    set_flag(FLAG_SWITCH_EVENT);
/*
    if (check_switch_timer == 0) {
	check_switch_timer=CHECK_SWITCH_PERIOD;
	switch_event_processing();
    }
    check_switch_timer--;
*/

//zero-detection event processing
    zero_detection_event_processing();
/*
    //TEMP MEASURE
    if ( ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN ) {
	ADC_StartConversion();
    } else if ( (ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN)==0 ) {

    }
*/
}
