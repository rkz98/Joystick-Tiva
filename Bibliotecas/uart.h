#ifndef BIBLIOTECAS_UART_H_
#define BIBLIOTECAS_UART_H_

#define UART_FR_TXFF 0x00000020 // UART Transmit FIFO Full
#define UART_FR_RXFE 0x00000010 // UART Receive FIFO Empty

void inicializarUART0(void);
unsigned char lerUART0(void);
void escreverUART0(unsigned char data);

#endif /* BIBLIOTECAS_UART_H_ */
