#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <Bibliotecas/uart.h>

void inicializarUART0()
{
    SYSCTL_RCGCUART_R |= 0x01;                        // activate UART0
    GPIO_PORTA_AFSEL_R |= 0x03;                       // enable alt funct on PA1-0
    GPIO_PORTA_PCTL_R |= 0x11;                        // enable UART funct on PA1-0

    UART0_CTL_R = 0x00;                               // disable UART
    UART0_IBRD_R = 8;                                 // IBRD = int(16.000.000 / (16 * 115.200)) = int(8,6805)
    UART0_FBRD_R = 44;                                // FBRD = int(0,6805 * 64 + 0.5) = 44
    UART0_LCRH_R = 0x70;                              // 8 bit word length (no parity bits, one stop bit, FIFOs)
    UART0_CC_R = 0x00;
    UART0_CTL_R = 0x301;                              // enable UART

    GPIO_PORTA_DEN_R |= 0x03;                         // enable digital I/O on PA1-0
}

unsigned char lerUART0(void)
{
    while ((UART0_FR_R & UART_FR_RXFE) != 0) { }
    return ((unsigned char)(UART0_DR_R&0xFF));
}

void escreverUART0(unsigned char data)
{
    while ((UART0_FR_R & UART_FR_TXFF) != 0) { }
    UART0_DR_R = data;
}
