#include "main.h"

volatile uint8_t conv_num;
volatile uint16_t conv_result;

extern uint8_t txbuf[UART_BUF_SIZE];	//for debug

extern volatile uint8_t flags;

extern uint16_t temp_adc[TEMP_LEVELS];


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


    TIM4_Config();
}

void ADC_StartConversion()
{
	ZERO_DETECT_PORT->CR2 &= ~ZERO_DETECT_PIN;	//disable zero_detect_pin interrupt

	conv_result=0;
	conv_num=16;

	ADC1->CR1 |= ADC1_CR1_ADON;	//start adc conversion
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



