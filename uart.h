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

#define UART_BAUDRATE 9600
#define UART_BUF_SIZE 32

void UART_Config(void);
void UART_SendStr(uint8_t *pbuf);

extern INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17);
extern INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18);

