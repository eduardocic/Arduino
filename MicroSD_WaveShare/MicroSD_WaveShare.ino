/*****************************************************************************
 *   A ideia inicial desse programa é fazer um log de dados fazendo obviamente
 * uso de um cartão Micro SD.
 * 
 *   É importante discorrer que para utilização dessa ferramenta, é importante
 * que fique claro que iremos utilizar a comunicação SPI. Mais informações...
 * 
 *   O dispositivo o qual eu possuo é da empresa 'WaveShare' e já possui, em 
 * princípio, os resistores necessários que alimentar todas as portas do dispo-
 * tivo diretamente com 3.3V. No caso, a saída do Arduino será 5V, mas a queda
 * de tensão é tal que eu tenho 3.3V entrando no cartão Micro SD.
 * 
 *   Em termos de ligação elétrica, com o arduino ainda não ligado na porta USB
 * da máquina, você conecta conforme:
 *
 *    ==============================================
 *    |     WaveShare        |       Arduino       |
 *    ==============================================
 *    |         MOSI         |   pino Digital 11   |
 *    |         MISO         |   pino Digital 12   | 
 *    |         SCLK         |   pino Digital 13   |
 *    |         CS           |   pino Digital 4    |
 *    |         3.3V         |   Alimentação 3.3V  |
 *    |         GND          |         GND         |
 *    ==============================================
 * 
 *   Agora você cria um arquivo de nome '*.txt', em que '*' diz respeito ao nome
 * de seu interesse. No meu caso, eu abri um arquivo EM BRANCO e salvei o mesmo
 * COMPLETAMENTE EM BRANCO com o nome 'mydata.txt'. Em seguida eu coloquei dentro
 * do cartão MicroSD. 
 * 
 *   Em seguida, eu acoplei o MicroSD no WaveShare, conectei o Arduino na porta
 * serial do PC e fiz o upload do código abaixo.
 *   
 *   
 *     Código
 *   ----------
 *   
 *   A primeira parte do código verifica se existe algum dispositivo MicroSD dis-
 * ponível. Essa verificação pode se dá via Serial ou por algum tipo de display 
 * de LED. Fica a critério do cliente. No meu caso, eu precisei verificar via 
 * Monitor Serial.
 * 
 *   A segunda parte, já dentro da função 'loop', a gente faz a inclusão apenas
 * dos números no arquivo.
 * 
 * 
 * Eduardo H. Santos
 * 08 de Novembro de 2018.
 *******************************************************************************/

/* Inclusão das bibliotecas a serem utilizadas no programa */
#include <SPI.h>
#include <SD.h>

/* Posição à qual estará ligado a seleção do chip para comunicação SPI */
const int chipSelect = 4;

/* Variável de controle a ser salva no MicroSD */
int i = 0;



/* =========================================================================
 *                                 
 *                                 SETUP
 *    
 * ======================================================================== */
void setup() {
  /* Abre a porta serial de comunicação */
  Serial.begin(9600);

  /* Espera a porta Serial abrir */
  while (!Serial) {}

  /* Tentativa de inicialização do Cartão */
  Serial.print("Inicializando o cartão...");

  /* Verifica se o cartão está presente e pode ser inicializado. */
  if (!SD.begin(chipSelect)) {
    Serial.println("Cartão com problema ou sem cartão");
    return;
  }
  Serial.println("Cartão inicializado com sucesso!!!");
}

/* =========================================================================
 *                                 
 *                                 LOOP
 *    
 * ======================================================================== */

void loop() {
  
  if (i <= 100){
   /* Para escrever no arquivo é importante abrir o mesmo e informar
    * que o arquivo aberto será apenas de leitura. */
    File dataFile = SD.open("mydata.txt", FILE_WRITE);  

    /* Se tivermos sucesso em abrir o arquivo, escreveremos nele
     * e é importante fechar o mesmo */
    if (dataFile) 
      dataFile.println(i);
      dataFile.close();

      /* Apenas um debug 'visual' para mim. */
      Serial.println(i);
    }
    i++;  
  }
  
  /* Uma vez o valor do 'i' ter chegado em 100 o microcontrolador não
   * faz mais nada */
  if ( i == 100 ) {}
}

