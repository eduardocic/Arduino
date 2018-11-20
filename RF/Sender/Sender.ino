/**************************************************************************
 *   Este programa foi realizado para enviar mensagens via RF para um outro
 * Arduino.
 * 
 *   O módulo RF é de 433MHz e é composto por dois dispositivos. Um menor,
 * que é o emissor e o menorzinho que é o receptor. 
 * 
 *   O emissor tem três pinos. Olhando de frente do mesmo, o que se tem é 
 * algo da forma:
 * 
 * 
 *            --------------
 *            |            |
 *            |            |
 *            |            |
 *            |            |
 *            --------------
 *              |    |   | 
 *              |    |   |
 *              |    |   |
 *             Dado Vcc GND
 *             
 *   O Vcc é ligado no 5V, o GND no ground mesmo e o Dado onde você             
 * desejar, sendo a saída digital.
 * 
 * 
 * Eduardo H. Santos
 * 19/11/2018.
 *************************************************************************/
#include <VirtualWire.h>
#include <string.h>


#define TAM_MAX_MENS   40
#define TECLA_ENTER    0x0D


int pino_envio_dados = 8;


void setup(){
  // =======================================================
  // Configurações para envio de informação:
  //
  // 1. pino ligado; e
  // 2. a quantidade de bits por segundo a serem enviados.
  // =======================================================
  vw_set_tx_pin(pino_envio_dados);
  vw_setup(2000);  

  Serial.begin(9600); 
  Serial.println("Digite o texto e aperte a tecla ENTER ");
}


void loop(){
  char dado[TAM_MAX_MENS];
  int  tam_mens_digitada;
  
  if (Serial.available() > 0)
  {
    // ===============================================================
    //   Em ASCII o sinal de retorno '\r' tem numeração 13. 
    // Dessa forma, a ideia é utilizar esse sinal para simbolizar
    // que efetivamente foi digitada uma mensagem. Tal sinal é
    // o valor da tecla ENTER.
    //
    //   A função Serial abaixo pega, portanto, o instante que é digi-
    // tada a tecla ENTER e salva uma string de TAM_MAX_MENS a mensa-
    // gem no buffer 'dado'.
    // ===============================================================
    tam_mens_digitada = Serial.readBytesUntil (TECLA_ENTER, dado, TAM_MAX_MENS);

    // Apenas para mostra a mensagem enviada.
    Serial.println();
    Serial.print("Mensagem enviada: ");
    Serial.print(dado);
    Serial.print("Tamanho da mensagem: ");
    Serial.println(tam_mens_digitada);
    
    // Envia a mensagem para a rotina que
    // transmite os dados via RF.
    send(dado);
    for (int i = 0 ; i< tam_mens_digitada ; i++){
      strcpy(&dado[i],'\0');
    }
  }  
} 

// ================================================================
// Função 'send' que recebe um array de char e envia a mensagem no
// formato abaixo.
// ================================================================
void send (char *message){
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); 
}
