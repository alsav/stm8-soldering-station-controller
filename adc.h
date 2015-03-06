

void ADC_Config();
void ADC_StartConversion();


extern INTERRUPT_HANDLER(ADC1_IRQHandler, 22);
extern INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23);
