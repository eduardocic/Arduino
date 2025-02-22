#include "DS1307.h"

// ================
//    Construtor
// ================
DS1307::DS1307 :
  tinyRTC(0x68)     // Endereço do dispositivo para comunicação I2C
{}


// ======================================
//  Ler os dados a partir do dispositivo
// ======================================
void DS1307::read_data_from_DS1307(){

  static char buffer[10];
  static int i = 0;

  // Apontamento do ponteiro para o endereço a partir de onde eu inicio a leitura.
  Wire.beginTransmission(this->tinyRTC);
  Wire.write(0x00);
  Wire.endTransmission();

  // Solicito, agora, 7 bytes do dispositivo.
  Wire.requestFrom(this->tinyRTC, 7);
  for (i = 0 ; i < 7 ; i++){
    buffer[i] = Wire.read();
  }

  // Recebo os bytes e salvo nas respectivas variáveis
  // (*) Essa conjugação de informações e variações dos eu tive que pegar do
  //     datasheet de modo a poder setar, shiftar e mesmo ajustar alguns valores
  //     informações a nível de registrador.
  // (*) Aparentemente está funcionando corretamente.
  this->segundo = (int)((buffer[0] >> 4)*10) + (int)(buffer[0] & 0x0F);
  this->minuto  = (int)((buffer[1] >> 4)*10) + (int)(buffer[1] & 0x0F);
  this->hora    = (int)((buffer[2] >> 4)*10) + (int)(buffer[2] & 0x0F);
  this->dia     = (int)(buffer[3] & 0x07);
  this->data    = (int)((buffer[4] >> 4)*10) + (int)(buffer[4] & 0x0F);
  this->mes     = (int)((buffer[5] >> 4)*10) + (int)(buffer[5] & 0x0F);
  this->ano     = (int)((buffer[6] >> 4)*10) + (int)(buffer[6] & 0x0F) + 2000;
}




// ===================================
//  Função que escreve no dispositivo
// ===================================
void DS1307::write_data_to_DS1307(char address, char value){
  Wire.beginTransmission(this->device);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}




// =============================================
//    Seta a data especificada no dispositivo
// =============================================
void set_date(enum Dias dia_na_semana, int dia_no_mes, enum Meses mes, int ano){

  // Variáveis a serem empregadas em vários parâmetros
  int bdc_High, bdc_Low, value;

  // Ajuste de dia da semana.
  writeToDevice(this->tinyRTC, DAY, dia_na_semana);

  // Ajuste de data.
  bdc_High = dia_no_mes/10;
  bdc_Low  = ddia_no_mes%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, DATE, value);

  // Ajuste do mês.
  bdc_High = mes/10;
  bdc_Low  = mes%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, MONTH, mes);

  // Ajuste do ano
  // (*) aqui tem que ser de 00 a 99. Faz o ajuste do ano + 2000
  //     depois por código.
  bdc_High = ano/10;
  bdc_Low  = ano%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, YEAR, value);
}



// =============================================
//    Seta a hora especificada no dispositivo
// =============================================
void DS1307::set_hour(int segundo, int minuto, int hora){

  // Variáveis a serem empregadas em vários parâmetros
  int bdc_High, bdc_Low, value;

  // Ajuste de segundos.
  bdc_High = segundo/10;
  bdc_Low  = segundo%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, SECONDS, value);

  // Ajuste de minutos.
  bdc_High = minuto/10;
  bdc_Low  = minuto%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, MINUTES, value);

  // Ajuste de hora.
  bdc_High = hora/10;
  bdc_Low  = hora%10;
  value    = (bdc_High << 4) | bdc_Low;
  writeToDevice(this->tinyRTC, HOURS, value);
}



// ==============================
//    Retorna o valor do ano
// ==============================
int DS1307::get_year(){
  return this->ano;
}



// ==============================
//    Retorna o valor do mês
// ==============================
int DS1307::get_month(){
  return this->mes;
}



// ===============================
//  Retorna o valor do dia no mês
// ===============================
int DS1307::get_date(){
  return this->data;
}



// ==================================
//  Retorna o valor do dia na semana
// ==================================
int DS1307::get_day(){
  return this->dia;
}



// ===========================
//   Retorna o valor da hora
// ===========================
int DS1307::get_hour(){
  return this->hora;
}



// =============================
//   Retorna o valor do minuto
// =============================
int DS1307::get_minute(){
  return this->minuto;
}



// ==============================
//   Retorna o valor do segundo
// ==============================
int DS1307::get_second(){
  return this->segundo;
}
