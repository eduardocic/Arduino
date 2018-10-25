// ==============================================================================
//
//                      Utilização do Sensor Mini Reed
//                      ------------------------------
// 
// (*) O presente programa pretende elucidar o funcionamento do sensor Mini Reed.
//
// (*) A ideia básica é mostrar como que funciona o sistema na utilização mais 
//     básica possível.
//
// (*) O sensor mini reed é composto por:
//
//     1. TRÊS PINOS ENTRADAS, onde lê-se escrito 'S'e '-'. Onde tem o 'S' é a 
//        posição para a captura do SIGNAL, e o '-' faz referência ao GROUND.
//        O pino central é onde deve ser conectado o VCC (5V);
//
//     2. Um resistor SMD de 10k;
//
//     3. O sensor reed.
//
// (*) O circuito é mais facilmente entendido conforme o diagrama abaixo:
//
//     +5V -------------
//                     |
//                   -----
//                   | R |
//                   -----            /
//                     |             /
//      GND ------------------------/    ---------- S
//           
// (*) A saída 'S' sempre estará em alta impedância caso não haja campo magnéti-
//     co próximo. Dessa forma, numa situação de leitura digital, o que se tará
//     é algo como '1'. Quando existe um campo magnético próximo, o sensor reed
//     fecha e com isso lê-se na saída 'S' o valor digital para o GND, no caso
//     o valor '0'.
//
// (*) Em resumo, quando se lê '1' a chave está aberta (ou seja, sem campo pró-
//     ximo) e quando se lê '0' a chave está fechada (ou seja, campo próximo).
//
// (*) O programa a seguir fará essa demonstração por acendimento do led ligado
//     ao pino digital 13 do arduino (na própria placa).
//
//   Eduardo H. Santos
//   24 de Outubro de 2018.
// ==============================================================================

int LED = 13;       
int MiniSensorReed = 2; 
int estadoSensor;     

void setup() 
{
  // Saída por LED para facilitar visualização.
  pinMode (LED, OUTPUT);
  
  // Porta à qual estará ligado o 'S' do sensor mini reed à porta especificada
  // em 'MiniSensorReed'.
  pinMode (MiniSensorReed, INPUT);
 
}

void loop()
{
  // Lê o valor do sensor por leitura digital e guarda o valor na variável inteira
  // 'estadoSensor'.
  estadoSensor = digitalRead(MiniSensorReed); 

  // Se a chave estiver aberta (ou seja, sem campo próximo), será lido alta impe-
  // dância (5V).
  if (estadoSensor == HIGH) {
    digitalWrite(LED, HIGH);
  }
  // Caso contrátio, será lido o valor do GND.
  else {
    digitalWrite(LED, LOW);
  }
}
