#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <stdio.h>
#include <stdlib.h>
#include <Bibliotecas/gpio.h>
#include <Bibliotecas/uart.h>
#include <Bibliotecas/adc.h>

uint32_t leituraAtual1 = 0, leituraAtual2 = 0, start = 0;
uint32_t leitura1aux[4], leitura2aux[4];

void configurarSystick(uint32_t tempoSystick)
{
    NVIC_ST_RELOAD_R = tempoSystick; //Recarrega após dar o tempo setado pela varíavel tempoSystick.
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE; //Ativa a interrupção pelo periférico da NVIC.
}

void interrupcaoSystick()
{
    leituraAtual1 = ADC0_SSFIFO0_R;
    leituraAtual2 = ADC1_SSFIFO0_R;

    if(start != 0)
    {
        leituraAIN6();
        leituraAIN7();
    }
}

void ativarPorts(uint32_t port)
{
    SYSCTL_RCGCGPIO_R = port; //Ativa todos os Ports.
}

void inicializarPinoB(uint32_t pinoB)
{
    GPIO_PORTB_DIR_R = 0x00; //Todo o PortB como DIGITAL INPUT
    GPIO_PORTB_DATA_R = pinoB;
    GPIO_PORTB_PUR_R = pinoB;

    GPIO_PORTB_IS_R = 0x00; //Selecionado a sensibilidade por borda
    GPIO_PORTB_IEV_R = pinoB; //Por ser pullup vai estar na borda de descida.
    GPIO_PORTB_IBE_R = 0x00; //Habilita as duas bordas. IBE - usado quando preciso das duas bordas na configuração, não precisa usar IS e IEV.

    GPIO_PORTB_DEN_R = pinoB;
    GPIO_PORTB_IM_R = pinoB; //Enable da interrupção, tem que vir depois do DEN, pois o botão pullup pode gerar uma interrupção.
}

void inicializarPinoC(uint32_t pinoC)
{
    GPIO_PORTC_DIR_R = 0x00; //Todo o PortC como DIGITAL INPUT.
    GPIO_PORTC_DATA_R = pinoC;
    GPIO_PORTC_PUR_R = pinoC;

    GPIO_PORTC_IS_R = 0x00; //Selecionado a sensibilidade por borda
    GPIO_PORTC_IEV_R = pinoC; //Por ser pullup vai estar na borda de descida.
    GPIO_PORTC_IBE_R = 0x00; //Habilita as duas bordas. IBE - usado quando preciso das duas bordas na configuração, não precisa usar IS e IEV.

    GPIO_PORTC_DEN_R = pinoC;
    GPIO_PORTC_IM_R = pinoC; //Enable da interrupção, tem que vir depois do DEN, pois o botão pullup pode gerar uma interrupção.
}

void inicializarPinoE(uint32_t pinoE)
{
    GPIO_PORTE_DIR_R = 0x00; //Todo o PortE como DIGITAL INPUT.
    GPIO_PORTE_DATA_R = 0x00;
    GPIO_PORTE_PUR_R = pinoE;

    GPIO_PORTE_IS_R = 0x00; //Selecionado a sensibilidade por borda
    GPIO_PORTE_IEV_R = pinoE; //Por ser pullup vai estar na borda de descida.
    GPIO_PORTE_IBE_R = 0x00; //Habilita as duas bordas. IBE - usado quando preciso das duas bordas na configuração, não precisa usar IS e IEV.

    GPIO_PORTE_DEN_R = pinoE;
    GPIO_PORTE_IM_R = pinoE; //Enable da interrupção, tem que vir depois do DEN, pois o botão pullup pode gerar uma interrupção.
}

void configurarPortB()
{
    if((GPIO_PORTB_RIS_R & 0x01) == 0x01) //ACAO_5
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(82); //R
        escreverUART0(75); //K
        escreverUART0(90); //Z
        escreverUART0(57); //9
        escreverUART0(56); //8
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTB_ICR_R = 0x01;
    }

    if((GPIO_PORTB_RIS_R & 0x02) == 0x02) //ACAO_6
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(76); //L
        escreverUART0(49); //1
        escreverUART0(78); //N
        escreverUART0(83); //S
        escreverUART0(78); //N
        escreverUART0(48); //0
        escreverUART0(87); //W
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTB_ICR_R = 0x02;
    }

    return;
}

void configurarPortC()
{
    if((GPIO_PORTC_RIS_R & 0x10) == 0x10) //ACAO_2
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(89); //Y
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTC_ICR_R = 0x10;
    }

    if((GPIO_PORTC_RIS_R & 0x20) == 0x20) //ACAO_3
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(79); //O
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTC_ICR_R = 0x20;
    }

    if((GPIO_PORTC_RIS_R & 0x40) == 0x40) //ACAO_4
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(35); //#
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTC_ICR_R = 0x40;
    }

    return;
}

void configurarPortD()
{
    return;
}

void configurarPortE()
{
    if((GPIO_PORTE_RIS_R & 0x01) == 0x01) //START
    {
        start = 1;

        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(83); //S
        escreverUART0(84); //T
        escreverUART0(65); //A
        escreverUART0(82); //R
        escreverUART0(84); //T
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x01;
    }

    if((GPIO_PORTE_RIS_R & 0x10) == 0x10) //ESQUERDA
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(76); //L
        escreverUART0(69); //E
        escreverUART0(70); //F
        escreverUART0(84); //T
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x10;
    }

    if((GPIO_PORTE_RIS_R & 0x02) == 0x02) //CIMA
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(85); //U
        escreverUART0(80); //P
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x02;
    }

    if((GPIO_PORTE_RIS_R & 0x08) == 0x08) //BAIXO
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(68); //D
        escreverUART0(79); //O
        escreverUART0(87); //W
        escreverUART0(78); //N
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x08;
    }

    if((GPIO_PORTE_RIS_R & 0x04) == 0x04) //DIREITA
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(82); //R
        escreverUART0(73); //I
        escreverUART0(71); //G
        escreverUART0(72); //H
        escreverUART0(84); //T
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x04;
    }

    if((GPIO_PORTE_RIS_R & 0x20) == 0x20) //ACAO_1
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(88); //X
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0('\r');
        escreverUART0('\n');

        GPIO_PORTE_ICR_R = 0x20;
    }

    return;
}

void leituraAIN6() //Eixo X
{
   ConverterLeitura(leituraAtual1, &leitura1aux);

   if( (leituraAtual1 < 5000) && (leituraAtual1 > 2300))
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(65); //A
        escreverUART0(78); //N
        escreverUART0(65); //A
        escreverUART0(76); //L
        escreverUART0(79); //O
        escreverUART0(71); //G
        escreverUART0(32); //Space
        escreverUART0(82); //R
        escreverUART0(73); //I
        escreverUART0(71); //G
        escreverUART0(72); //H
        escreverUART0(84); //T
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0(32); //Space
        escreverValorLeitura(&leitura1aux);
        escreverUART0('\r');
        escreverUART0('\n');
    }

    else if( (leituraAtual1 >= 1) && (leituraAtual1 < 1800))
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(65); //A
        escreverUART0(78); //N
        escreverUART0(65); //A
        escreverUART0(76); //L
        escreverUART0(79); //O
        escreverUART0(71); //G
        escreverUART0(32); //Space
        escreverUART0(76); //L
        escreverUART0(69); //E
        escreverUART0(70); //F
        escreverUART0(84); //T
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0(32); //Space
        escreverValorLeitura(&leitura1aux);
        escreverUART0('\r');
        escreverUART0('\n');
    }

    return;
}

void leituraAIN7() //Eixo Y
{
    ConverterLeitura(leituraAtual2, &leitura2aux);

    if((leituraAtual2 < 5000) && (leituraAtual2 > 2300))
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(65); //A
        escreverUART0(78); //N
        escreverUART0(65); //A
        escreverUART0(76); //L
        escreverUART0(79); //O
        escreverUART0(71); //G
        escreverUART0(32); //Space
        escreverUART0(85); //U
        escreverUART0(80); //P
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0(32); //Space
        escreverValorLeitura(leitura2aux);
        escreverUART0('\r');
        escreverUART0('\n');
    }

    else if( (leituraAtual2 >= 1) && (leituraAtual2 < 1800))
    {
        escreverUART0(40); //(
        escreverUART0(32); //Space
        escreverUART0(65); //A
        escreverUART0(78); //N
        escreverUART0(65); //A
        escreverUART0(76); //L
        escreverUART0(79); //O
        escreverUART0(71); //G
        escreverUART0(32); //Space
        escreverUART0(68); //D
        escreverUART0(79); //O
        escreverUART0(87); //W
        escreverUART0(78); //N
        escreverUART0(32); //Space
        escreverUART0(41); //)
        escreverUART0(32); //Space
        escreverValorLeitura(leitura2aux);
        escreverUART0('\r');
        escreverUART0('\n');
    }

    return;
}

int ConverterLeitura(uint32_t numero, uint32_t *buf)
{
    uint32_t i = 0;

    while (numero != 0)
    {
        buf[i++]  = numero % 10;
        numero  = numero / 10;
    }
}

void escreverValorLeitura(uint32_t *buf)
{
    escreverUART0(buf[3]+48);
    escreverUART0(buf[2]+48);
    escreverUART0(buf[1]+48);
    escreverUART0(buf[0]+48);
}

int main(void)
{
    configurarSystick(200000); //50m = 200000
    ativarPorts(PORT_TODOS);

    inicializarPinoB(PINOSB_SETADOS);
    inicializarPinoC(PINOSC_SETADOS);
    inicializarPinoE(PINOSE_SETADOS);

    ativarADC();
    configurarADC0();
    configurarADC1();

    inicializarUART0();

    NVIC_EN0_R = 0x1E; //Página 104, cada GPIO tem um bit.

    while(1)
    {

    }

    return 0;
}
