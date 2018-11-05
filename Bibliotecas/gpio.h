#ifndef BIBLIOTECAS_GPIO_H_
#define BIBLIOTECAS_GPIO_H_

#include <inttypes.h>
#include <tm4c123gh6pm.h>

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
#define PORT_E 4
#define PORT_F 5
#define PORT_TODOS 0x3F

#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PE0 0
#define PE1 1
#define PE2 2
#define PE3 3
#define PE4 4
#define PE5 5
#define PE6 6
#define PE7 7

#define PF0 0
#define PF1 1
#define PF2 2
#define PF3 3
#define PF4 4
#define PF5 5
#define PF6 6
#define PF7 7

#define PINOSB_SETADOS 0x03
#define PINOSC_SETADOS 0x70
#define PINOSE_SETADOS 0x3F

#define BOTAO_ANALOGICO1 PD0
#define BOTAO_ANALOGICO2 PD1

#define BOTAO_START PE0
#define BOTAO_CIMA PE1
#define BOTAO_BAIXO PE2
#define BOTAO_ESQUERDA PE3
#define BOTAO_DIREITA PE4

#define BOTAO_ACAO1 PE5
#define BOTAO_ACAO2 PC4
#define BOTAO_ACAO3 PC5
#define BOTAO_ACAO4 PC6
#define BOTAO_ACAO5 PB0
#define BOTAO_ACAO6 PB1

#define ler_BIT(registrador, bit) (((registrador) >> (bit)) & 0x01)
#define setar_BIT(registrador, bit) ((registrador) |= (1 << (bit)))
#define limpar_BIT(registrador, bit) ((registrador) &= ~(1 << (bit)))
#define escrever_BIT(registrador, bit, valorBit) (valorBit ? setar_BIT(registrador, bit) : limpar_BIT(registrador, bit))

int lerPino(volatile uint32_t *registrador, uint32_t pino);
void setarPino(volatile uint32_t *registrador, uint32_t pino, uint32_t valor);
void configurarPino(volatile uint32_t *port_dir, uint32_t *port_den, int pino, int modo);

#endif /* BIBLIOTECAS_GPIO_H_ */
