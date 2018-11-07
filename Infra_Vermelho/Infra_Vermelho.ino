/*******************************************************************
 * A biblioteca RobotIRremote estava zoada. Então eu baixei a
 * biblioteca que funciona que é a 'IRremote'. Então se for 
 * utilizar alguma coisa com InfraVermelho, use a IRremote que a
 * mesma funciona direitinho.
 * 
 * O circuito em si apresenta um sensor que quando visto de frente
 * é algo da forma:
 * 
 *              ---------------
 *              |    .....    |
 *              |   .     .   |
 *              |  .       .  |
 *              |   .     .   |
 *              |    .....    |
 *              |             |
 *              ---------------                
 *                /    |    \
 *               /     |     \  
 *              |      |      |
 *              |      |      |
 *              |      |      | 
 *              |      |      | 
 *               
 *             sinal   GND    +5V
 *               
 *                
 * Eduardo H. Santos
 * 06/11/2018
 *******************************************************************/
#include "IRremote.h"

// Em qual pino digital irei ligar o sensor de IR?
int pino_IR = 11;  
unsigned long valor;

// Criação dos objetos que serão utilizados no nosso sistema.
IRrecv         irrecv(pino_IR);
decode_results resultado;

void setup()
{
  // Inicia a comunicação serial.
  Serial.begin(9600);
  
  // Inicia o sistema de recepção de IR.
  irrecv.enableIRIn(); 
}

void loop() 
{ 
  // Identifica se existe recepção de sinal.
  if (irrecv.decode(&resultado)){
    
      Serial.print("Valor lido : ");  
      // Olhando na biblioteca, a variável '*.value'  é do tipo 
      // 'unsigned long, ou seja, de 32-bits.
      valor = resultado.value;
      Serial.println(valor, HEX);  
      irrecv.resume();   
  }
}

