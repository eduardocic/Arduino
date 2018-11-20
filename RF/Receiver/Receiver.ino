#include <VirtualWire.h>
#include <LiquidCrystal.h>

// Pino digital que seŕa utilizado para receber o sinal de RF.
int pino_recebe_dados = 5;

// Para mostrar na tela de LCD a mensagem recebida.
LiquidCrystal Display_LCD(2, 3, 7, 8, 9, 10);

// =========================================================================
//  'Virtual Wire Maximo Message Lenght' = VW_MAX_MESSAGE_LEN
// 
//   Isso está no .cpp da biblioteca.
// =========================================================================
uint8_t messagem[VW_MAX_MESSAGE_LEN];     // Armazena a mensagem recebida 
uint8_t msgTamanho = VW_MAX_MESSAGE_LEN;  // Armazena o tamanho das mensagens

void setup(){
  Serial.begin(9600);
  
  Display_LCD.begin(16, 2);
  // Define o pino 5 do Arduino como entrada 
  // de dados do receptor
  vw_set_rx_pin(pino_recebe_dados); 
  
  // Bits por segundo. Tem de estar de acordo com o 'Sender'.
  vw_setup(2000);

  // Inicializa o receptor
  vw_rx_start();              
}
 
void loop(){
  // ==========================================================
  // Essa função verifica se há mensagem sendo recebida.
  // Se sim, pega o tamanho da mensagem e salva no buffer
  // do tipo uint8_t. 
  // ==========================================================
  if (vw_get_message(messagem, &msgTamanho)){
    /* Limpa a tela */
    Display_LCD.clear();
  
    /* Posiciona o cursor na coluna 0, linha 0 */
    Display_LCD.setCursor(0, 0);
    Display_LCD.print(msgTamanho);
    Display_LCD.print(' ');
    Display_LCD.print((char *)messagem);

//    for (int i = 0 ; i < msgTamanho ; i++){
//      messagem[i] = 0;
//    }
  }
}
