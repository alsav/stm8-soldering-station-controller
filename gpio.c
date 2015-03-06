#include "main.h"

extern volatile uint8_t flags;
//extern uint8_t temp_lvl;


void GPIO_Config() {



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



}








INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
}

INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
}

INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
}


//zero-detection exti handler
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{

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
}
