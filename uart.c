#include "main.h"


volatile uint8_t *pbuf_tx;
uint8_t txbuf[UART_BUF_SIZE];

void putchar(char c) {
    // Write a character to the UART1
//    UART1_SendData8(c);
    // Loop until the end of transmission
//    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

//    return (c);

    while(!(UART1->SR & UART1_SR_TXE));
    UART1->DR = c;
}


void UART_Config() {
//    UART1_DeInit();
    /* UART1 and UART3 configuration -------------------------------------------------*/
    /* UART1 and UART3 configured as follow:
          - BaudRate = 9600 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Receive and transmit enabled
          - UART1 Clock disabled
     */
    // Configure the UART1
//    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
//                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);

/*
    uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;

    // Clear the word length bit 
    UART1->CR1 &= (uint8_t)(~UART1_CR1_M);

    // Set the word length bit according to UART1_WordLength value
    UART1->CR1 |= (uint8_t)UART1_WORDLENGTH_8D;

    // Clear the STOP bits
    UART1->CR3 &= (uint8_t)(~UART1_CR3_STOP);
    // Set the STOP bits number according to UART1_StopBits value
    UART1->CR3 |= (uint8_t)UART1_STOPBITS_1;

    // Clear the Parity Control bit
    UART1->CR1 &= (uint8_t)(~(UART1_CR1_PCEN | UART1_CR1_PS  ));
    // Set the Parity Control bit to UART1_Parity value
    UART1->CR1 |= (uint8_t)UART1_PARITY_NO;

    // Set the UART1 BaudRates in BRR1 and BRR2 registers according to UART1_BaudRate value
    BaudRate_Mantissa    = ((uint32_t)CLK_GetClockFreq() / (UART_BAUDRATE << 4));
    BaudRate_Mantissa100 = (((uint32_t)CLK_GetClockFreq() * 100) / (UART_BAUDRATE << 4));
    // Set the fraction of UART1DIV
    UART1->BRR2 |= (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8_t)0x0F);
    // Set the MSB mantissa of UART1DIV
    UART1->BRR2 |= (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0);
    // Set the LSB mantissa of UART1DIV
    UART1->BRR1 |= (uint8_t)BaudRate_Mantissa;
*/



    /* Enable UART1 Transmit interrupt*/
//    UART1_ITConfig(UART1_IT_TXE, ENABLE);
//    UART1->CR2 |= UART1_CR2_TIEN;

//    enableInterrupts();
}


void UART_SendStr(uint8_t *pbuf)
{

    if (*pbuf && (UART1->SR & UART1_SR_TXE)) {
//	STATUS_LED_ON;
	pbuf_tx = pbuf;
	UART1->DR = *pbuf_tx;
	pbuf_tx++;
	UART1->CR2 |= UART1_CR2_TIEN; //enable txe empty interrupt
}
//    }
}


INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
{
    if (UART1->SR & UART1_SR_TXE) {
	if (*pbuf_tx) {
	    UART1->DR = *pbuf_tx;
	    pbuf_tx++;
	} else {
	    UART1->CR2 &= ~UART1_CR2_TIEN; //disable txe empty interrupt
//	    STATUS_LED_OFF;
    }
}

    /* Write one byte to the transmit data register */
//    UART1_SendData8(TxBuffer1[IncrementVar_TxCounter1()]);
  
//    if (GetVar_TxCounter1() == GetVar_NbrOfDataToTransfer1())
//    {
        /* Disable the UART1 Transmit interrupt */
//        UART1_ITConfig(UART1_IT_TXE, DISABLE);
//    }
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
    /* Read one byte from the receive data register */
//    RxBuffer1[IncrementVar_RxCounter1()] = UART1_ReceiveData8();

//    if (GetVar_RxCounter1() == GetVar_NbrOfDataToRead1())
//    {
        /* Disable the UART1 Receive interrupt */
//        UART1_ITConfig(UART1_IT_RXNE_OR, DISABLE);
//    }
}

