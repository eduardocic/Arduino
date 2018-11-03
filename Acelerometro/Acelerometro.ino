#include <Wire.h>

/*************************************************************************
 *  1. De acordo com o datasheet to MMA 7660, o endereço do mesmo é o 0x4C.
 *     Esta informação pode ser obtida na página 23 do referido documento 
 *     com o link dispobilizado abaixo:
 * 
 *       https://www.nxp.com/docs/en/data-sheet/MMA7660FC.pdf
 * 
 * 
 *  2. A ideia é configurar o referido dispositivo primeiro para 
 *     depois utilizá-lo. 
 *    
 *  3. Para configurar o dispositivo, a gente tem que ditar as re-
 *     gras às quais ele deve seguir. Para tal, a gente tem que
 *     escrever em determinados registradores algumas informações.
 *     Em termos sequenciais a gente faz é o seguinte:
 *    
 *     a) Informar em qual dispositivo iremos escrever;
 *     b) Informar em qual registrador do dispositivo iremos escrever; e
 *     c) Informar qual valor será escrivo no registrador.
 *    
 *     Agindo dessa forma, a gente simplesmente configura o dispositivo
 *     para ele funcionar como a gente deseja.
 * 
 *  4. Para ler as informações do dispositivo, o que a gente faz é:
 *    
 *     a) Informar de qual disposotivo iremos ler; e
 *     b) Informar qual o registrador será lido.
 * 
 *  5. Em termos de configuração e ligação entre os dispositivos, para o
 *     Arduino UNO, o que a gente tem é:
 *    
 *     ====================================
 *     |    MMA 7660     |  Arduino UNO   |
 *     ====================================
 *     |       Vcc       |      3.3V      |
 *     ------------------------------------
 *     |       GND       |       0V       |
 *     ------------------------------------
 *     |       SCL       |       A5       |
 *     ------------------------------------
 *     |       SDA       |       A4       |
 *     ------------------------------------
 *    
 *  6. Num primeiro momento, o que a gente irá fazer é ler apenas as acele-
 *     rações dos três eixos do do acelerômetro.
 *    
 *  7. Em termos de configuração, eu desejarei ter 1 informação por segundo.  
 *     (one sample for 1 second);
 *    
 *  8. A gente pode configurar para alguns parâmetros detalhados na página 11.
 *  
 *  9. Em termos de configuração, você tem de setar os parâmetros conforme
 *     disponível na função 'setup' e já explicado no tópico '3'.
 *  
 * 10. Quando solicitados os bytes relativos à aceleração, aparentemente o 
 *     ponteiro do 'request' inicialmente está setado para o registrador 0x00
 *     que é o do XOUT. Ele é incrementado de acordo com os requests que são
 *     determinados pelo operador. No caso, eu preciso apenas de 3 valores
 *     que dizem respeito as acelerações em x, y e z. Dessa forma eu faço um
 *     request apenas de 3 bytes.
 * --------------------------------------------------------------------------
 *  Eduardo H. Santos  
 *  Data: 03/11/2018 
 ***************************************************************************/

// Dispositivo de endereço de 7 bits: 1101100 -- Acelerômetro.
byte Acelerometro = 0x4C;

// Configuração de modo de operação. No caso queremos modo ACTIVE.
byte MODE = 0x07;

// Registradores para pegar as acelerações.
byte XOUT = 0x00;
byte YOUT = 0x01;
byte ZOUT = 0x02;

// Demais registradores para configurar que desejamos as informações em uma
// taxa de 1 amostra por segundo com a filtragem de 8 medidas de forma
// que a resposta dada já apresente um resultado filtrado.
byte SR   = 0x08;


byte x, y, z;

void setup(){
  // Inicia a serial;
  Serial.begin(9600);
  
  // Iniciar a transmissão 'Wire'.
  // -----------------------------
  Wire.begin();

  // 1. Configurar o acelerômetro para que ele funcione no modo ativo.
  // -----------------------------------------------------------------
  Wire.beginTransmission(Acelerometro);
  Wire.write(MODE);             
  Wire.write(0x01);
  Wire.endTransmission();    

  // 2. Configurar o acelerômetro para que ele forneça a informação 
  //    sempre em 1s. Ademais, quero que esse informação passe por
  //    um filtro de 8 janelas. 
  // ---------------------------------------------------------------
  Wire.beginTransmission(Acelerometro);
  Wire.write(SR);             
  Wire.write(0xE7);
  Wire.endTransmission();   

  // Apenas para estabilizar a malha.
  // --------------------------------
  delay(100);
}

void loop()
{
  // Lendo os dados do endereço de XOUT, YOUT e ZOUT.
  // ------------------------------------------------
  Wire.requestFrom(Acelerometro, byte(3));
  if ( Wire.available() >= 1 ){
    x = Wire.read();
    y = Wire.read();
    z = Wire.read();    
  }    
  Wire.endTransmission();
  

  // Eliminando qualquer termo que exista nos bits 7 e 8 do registrador.
  // -------------------------------------------------------------------
  x = (x << 2)/4;
  y = (y << 2)/4;
  z = (z << 2)/4;

  // Falta apenas criar um código para utilização da álgebra do comple-
  // mento 2.



  // Amostra o resultado no terminal.
  // --------------------------------
  Serial.print("Valores: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  delay(1000);
}
