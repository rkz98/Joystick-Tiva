#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <Bibliotecas/gpio.h>

int lerPino(volatile uint32_t *registrador, uint32_t pino)
{
    return ler_BIT(*(registrador), pino);
}

void setarPino(volatile uint32_t *registrador, uint32_t pino, uint32_t valor)
{
    escrever_BIT(*(registrador), pino, valor);
}

void configurarPino(volatile uint32_t *port_dir, uint32_t *port_den, int pino, int modo)
{
    escrever_BIT(*(port_dir), pino, modo);
    escrever_BIT(*(port_den), pino, 1);
}


