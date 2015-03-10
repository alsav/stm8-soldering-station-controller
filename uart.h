#define UART_BAUDRATE 9600
#define UART_BUF_SIZE 32

void UART_Config(void);
void UART_SendStr(uint8_t *pbuf);

extern INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17);
extern INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18);

