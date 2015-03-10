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


volatile uint8_t *pbuf_tx;
uint8_t txbuf[UART_BUF_SIZE];

void putchar(char c) {
    while(!(UART1->SR & UART1_SR_TXE));
    UART1->DR = c;
}


void UART_Config() {

    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);

}


void UART_SendStr(uint8_t *pbuf)
{

    if (*pbuf && (UART1->SR & UART1_SR_TXE)) {
	pbuf_tx = pbuf;
	UART1->DR = *pbuf_tx;
	pbuf_tx++;
	UART1->CR2 |= UART1_CR2_TIEN; //enable txe empty interrupt
    }
}

INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
{
    if (UART1->SR & UART1_SR_TXE) {
	if (*pbuf_tx) {
	    UART1->DR = *pbuf_tx;
	    pbuf_tx++;
	} else {
	    UART1->CR2 &= ~UART1_CR2_TIEN; //disable txe empty interrupt
	}
    }

}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
}

