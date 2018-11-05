#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <Bibliotecas/adc.h>

void ativarADC()
{
    SYSCTL_RCGCADC_R = 0x03; //Ativar o clock no periférico ADC0 e ADC1. Possui 2 ADC em cada Port: ADC0 e ADC1.
    GPIO_PORTD_AFSEL_R = 0x03; //A função principal em todo port é o GPIO. Aqui selecionamos a função alternativa do port.
    GPIO_PORTD_AMSEL_R = 0x03; //Defino que a minha função alternativa é o analógico.
}

void configurarADC0()
{
    ADC0_ACTSS_R = 0x00; //Zera a fila de trabalho. SEMPRE INICIAR 0x00.
    ADC0_EMUX_R = 0x0F; //Multiplexador de evento. Seto quando quero que uma nova conversão aconteça (Trigger) -- Automatiza as conversões.
    ADC0_SSMUX0_R = 0x06; //0x06 AIN6 //Posicionamento da fila 0. indica a sequência da fila de trabalho que queremos ler.
    ADC0_SSCTL0_R = 0x02; //Registrador de controle da fila. indica a ultima posição da fila 0
    ADC0_ACTSS_R = 0x01; //Ativa a fila 0. //Fila de trabalho do ADC0. No hardware sempre tem 4 posições que vão ler o ADC0. Aqui avisamos o limite para o hardware.
    ADC0_PSSI_R = 0x01; //Inicializador da fila 0.
}

void configurarADC1()
{
    ADC1_ACTSS_R = 0x00; //Zera a fila de trabalho. SEMPRE INICIAR 0x00.
    ADC1_EMUX_R = 0x0F; //Multiplexador de evento. Seto quando quero que uma nova conversão aconteça (Trigger) -- Automatiza as conversões.
    ADC1_SSMUX0_R = 0x07; //0x7 pelo //Posicionamento da fila 0. indica a sequência da fila de trabalho que queremos ler.
    ADC1_SSCTL0_R = 0x02; //Registrador de controle da fila. indica a ultima posição da fila 0
    ADC1_ACTSS_R = 0x01; //Ativa a fila 0. //Fila de trabalho do ADC1. No hardware sempre tem 4 posições que vão ler o ADC1. Aqui avisamos o limite para o hardware.
    ADC1_PSSI_R = 0x01; //Inicializador da fila 0.
}

