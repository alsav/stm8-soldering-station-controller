//#include "stm8s.h"
//#include "stm8s_gpio.h"

#include "main.h"

//HSI 2MHZ - default val(?)

//static uint8_t *str1="Ok qwertyuiop\r\n";
//static uint8_t *str2="asdfgh\r\n";

uint8_t check_switch_timer;

extern volatile uint8_t flags;
extern volatile uint8_t temp_lvl;
extern volatile uint8_t heat_counter;
extern uint8_t txbuf[UART_BUF_SIZE];	//for debug
extern volatile uint16_t conv_result;

extern int8_t heat_cycles;		//pid regulated value
extern uint16_t temp_adc[TEMP_LEVELS];

pid_struct pid = {
    0, 0,		//dstate, istate
    3, -3,		//imax, imin
    50, 0,
    1, 1, 1		//p, i, d gains
};




static void delay(uint32_t t)
{
  while(t--);
}

/*
void test_out()
{
    uint32_t clock;
    uint8_t tmp;


    clock=CLK_GetClockFreq();
    printf("Clock freq: %d\r\n",clock);
    tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
    tmp = (uint8_t)(tmp >> 3);
    printf("HSIDIV: %d\r\n",tmp);

}
*/


int main( void )
{
    uint8_t i=0;

    disableInterrupts();

    GPIO_Config();
    UART_Config();
    ADC_Config();
//    TIM4_Config();

    flags=0;
    temp_lvl=0;
    LEDS_OFF;

    heat_counter = HEAT_IDLE_CYCLES;
    check_switch_timer=CHECK_SWITCH_PERIOD;

    enableInterrupts();

//HEATER_ON;
//    test_out();
    UART_SendStr("OK!\r\n");

    while(1) {
//	delay(20000);
//	delay(2000);
	//UART1_SendData8('!');
//	printf_tiny("Ok\r\n");
//	printf("%c\n\r", 'p');

//	printf("Ok\r\n");
//	UART_SendStr("Ok\r\n");
/*
	if (q)
	    UART_SendStr(str1);
	else 
	    UART_SendStr(str2);
    q=1-q;
*/

/*
    if (get_flag(FLAG_SWITCH_PRESSED))
	HEATER_ON;
    else
	HEATER_OFF;
*/

    //pid processing and output debug msg
    if (get_flag(FLAG_END_ADC_CONV)) {

	heat_cycles = update_pid(&pid, (int8_t) (temp_adc[temp_lvl] - conv_result), conv_result);
	reset_flag(FLAG_END_ADC_CONV);
	sprintf(txbuf,"%d,%d %d %d:%d\r\n",conv_result,(uint16_t)(temp_lvl), (int16_t)heat_cycles, (int16_t)(pid.dstate),(int16_t)(pid.istate));
	UART_SendStr(txbuf);	//send result to uart
    }


    //switch event processing
    if (get_flag(FLAG_SWITCH_EVENT)) {

	reset_flag(FLAG_SWITCH_EVENT);

	if (check_switch_timer == 0) {
	    check_switch_timer=CHECK_SWITCH_PERIOD;
//	    switch_event_processing();

UART1->DR = '!';
	    if ( (SWITCH_PORT->IDR & SWITCH_PIN) && get_flag(FLAG_SWITCH_PRESSED) ) {			//if key is released (pull-up)
		UART1->DR = '=';
		reset_flag(FLAG_SWITCH_PRESSED);
	    } else if ( ((SWITCH_PORT->IDR & SWITCH_PIN) == 0) && !get_flag(FLAG_SWITCH_PRESSED) ) {	//if key is pressed
		UART1->DR = '_';
		set_flag(FLAG_SWITCH_PRESSED);
		temp_lvl = (temp_lvl+1) % 8;
		LEDS_SET(temp_lvl);
	    }

	    check_switch_timer--;
	}

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






#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
