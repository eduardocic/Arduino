#ifndef _DS_1307_H_
#define _DS_1307_H_

// *****************************************************************
// (*) Para utilização da DS1307, empregado na plaquinha tinyRTC
//     é fundamental que a gente faça a ligação eletrônica do sis-
//     tema:
//
//            ------------------------------------------
//            |     tinyRTC       |       Arduino      |
//            ------------------------------------------
//            |        VCC        |         5V         |
//            |        GND        |         GND        |
//            |        SDA        |         A4*        |
//            |        SCL        |         A5*        |
//            ------------------------------------------
//            (*) Analog Input (entrada analógica)
//
// (*) Estou empregando como referências as informações muito bem
//     explicada disponíveis na série de três artigos disponíveis
//     neste link:
//
//      https://embarcados.com.br/modulo-tiny-rtc-i2c-parte-2/
//
//
// (*) Eu achei o código dele meio confuso (eu sempre acho os
//     códigos dos outros confusos), de modo que eu programei na unha
//     todas as estruturas, enum's, funções e afins desse programa
//     para o relógio. As informações do funcionamento eu busquei
//     diretamente do datasheet mesmo (nada muito complicado de se
//     ler).
//
// (*) Para a biblioteca de LowPower, favor consultar o seguinte
//     link:
//
//          https://github.com/rocketscream/Low-Power
//
// Eduardo Henrique dos Santos
// 07/07/2024
// *****************************************************************
#include "Wire.h"                // Para ativar comunicação I2C

// Endereço dos registradores
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS   0x02
#define DAY     0x03
#define DATE    0x04
#define MONTH   0x05
#define YEAR    0x06




class DS1307 {

  public:

    DS1307();
    void read_data_from_DS1307();
    void write_data_to_DS1307(char address, char value);
    void set_date(enum Dias, int, enum Meses, int);
    void set_hour(int, int, int);
    int get_year();
    int get_month();
    int get_date();
    int get_day();
    int get_hour();
    int get_minute();
    int get_second();



  private:
    // Endereço do dispositivo DS1307 (chip do tinyRTC)
    const int tinyRTC;
    enum Dias  {DOMINGO = 1, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO};
    enum Meses {JANEIRO = 1, FEVEREIRO, MARCO, ABRIL, MAIO, JUNHO, JULHO, AGOSTO, SETEMBRO, OUTUBRO, NOVEMBRO, DEZEMBRO};

    unsigned int segundo;
    unsigned int minuto;
    unsigned int hora;
    unsigned int dia;
    unsigned int data;
    unsigned int mes;
    unsigned int ano;
};












#endif
