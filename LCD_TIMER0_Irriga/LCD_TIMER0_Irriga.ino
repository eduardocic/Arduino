/*********************************************************
 * 
 * Autor: Eduardo H. Santos.
 * Data:  06 de Setembro de 2018
 * 
 * 
 * Resumo: 
 * 
 *    Este programa é um relógio de 1s de precisão
 *    o qual será utilizado no meu sistema de irri-
 *    gação automático.
 *         
 * 
 * Explicação:
 * 
 *   1. Farei a programação para que haja a interrupções
 *      no TIMER0 de forma a atualizar as variáveis a 
 *      cada 1s. Isso me dará uma boa base temporal para
 *      a confecção da lógica que se dará para aguar o
 *      sistema uma vez por dia durante um determinado
 *      período de tempo.
 *      
 *   2. A interrupção por TIMER0 neste caso ocorrerá 
 *      quando o valor do registrador TCNT0 (o qual será
 *      atualizado a cada 'clock' do sistema) for igual
 *      ao valor salvo no registrador OCR0A.
 *   
 *   3. Eu setei um prescale para o meu uC de 1024. Dessa     
 *      forma o TCNT0 terá a atualização de valor de 
 *      forma incremetal quando o Cristal interno oscilar
 *      1024 vezes. Como o Cristal externo é de 16MHz, 
 *      significa fizer que o TCNT0 será incrementado na 
 *      taxa de (16 MHz)/(1024) = 15.625 Hz. 
 *   
 *   4. A frequência do TCNT0 sendo 15.625 Hz significa
 *      dizer que a cada 0,000064s haverá um incremento
 *      no TCNT0. Para eu ter a bumbo de 1s de precisão,
 *      eu preciso trabalhar em cima deste tempo de forma
 *      a atualizar o meu sistema nessa taxa.
 *      
 *   5. Criarei uma variável do tipo 'static int' de for-
 *      ma a ser atualizara a cada interrupção por timer.
 *   
 *   6. Pelas relações matemáticas, se eu multiplicar
 *      0,000064s por 125 e depois por 125 novamente, eu
 *      terei precisamente 1s. 
 *      
 *   7. Assim, inicialmente eu inicializarei o OCR0A com
 *      o valor de 125. Com isto, a cada 125*0,000064s
 *      ocorrerá uma interrupção por TIMER0. Com isto, 
 *      a interrupção ocorrerá a cada 0,008s.
 *      
 *   8. Atualizarei, então, a variável 'static int' até
 *      atingir o valor de 125. Isto me dará um bumbo de 
 *      1s de precisão.
 *      
 *   9. Apresentarei os valores das horas no display de 
 *      LCD.
 ********************************************************/
#include <LiquidCrystal.h>

/********************************************************
 * 
 *  Variáveis utilizadas no meu sistema.
 *  
 *  Definirei as variáveis como estáticas
 *  apesar de serem globais
 *  
 ********************************************************/
#define LED  13
#define RELE 10
 
static int cont    = 0;
static int segundo;
static int minuto;
static int hora;
static int dia;
int        T = 4;  // Tempo de acionamento do relé.

static char stringHora[10];

//LiquidCrystal Display_LCD(12, 11, 5, 4, 3, 2); // Código -- FelipeFlop
//LiquidCrystal Display_LCD(7, 6, 5, 4, 3, 2);   // Funciona beleza -- Teste 1 (Eduardo);
LiquidCrystal Display_LCD(2, 3, 4, 5, 6, 7);     // Funcionou beleza.

/********************************************************
 * Em termos de conexão elétrica, faça:
 * 
 * ----------------------------------
 *     Display    ||    Arduino     |
 * ----------------------------------
 *      Vss               GND
 *      VDD               5V
 *      V0                Pot
 *      RS                D2
 *      RW                GND
 *      E                 D3
 *      D0              -------
 *      D1              -------
 *      D2              -------
 *      D3              -------
 *      D4                D4
 *      D5                D5
 *      D6                D6
 *      D7                D7
 *      A                 5V
 *      K                 GND
 ********************************************************/



/******************************************************** 
 *  
 *  Protótipo das funções.
 *  
 ********************************************************/
void initTime(int _dia, int _hora, int _minuto, int _segundo);
void configTimer0();
void imprimeSerial();
void imprimeLCD();


/******************************************************** 
 *  
 *  Função 'setup'
 *  
 ********************************************************/
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(RELE, OUTPUT);
    
  configTimer0();
  initTime(0, 6, 59, 50);
  
  Serial.begin(9600);
  Display_LCD.begin(16, 2);
}


/******************************************************** 
 *  
 *  Função 'loop'
 *  
 ********************************************************/
void loop() {
  
}


/******************************************************** 
 *  
 *  Função de tratamento de interrupção
 *  
 ********************************************************/
ISR(TIMER0_COMPA_vect)
{
   
   /* Atualizado a cada 0,008s. */
   cont++;

   /* Este evento acontece apenas quando se completa 1s. */
   /* if(cont == 125){ // Por experiência empírica, eu vi que atrasa muito com 125. */
   if(cont == 124){
     cont = 0;
     segundo++;

     if ( segundo == 60 ){
       minuto++;
       segundo = 0;
       if ( minuto == 60 ){
         hora++;
         minuto = 0;
         if ( hora == 24 ){
           dia++;
           hora = 0;
         }
       }
     }


     if ( (hora == 7) && (minuto == 0) && (segundo == 0) ){
        digitalWrite(RELE, HIGH);
     }
     if ( (hora == 7) && (minuto == 0) && (segundo == T) ){
        digitalWrite(RELE, LOW);
     }

  
//     static int flag = 0;   
//     /* Alerta por LED para acompanhamento da atividade. */
//     if (flag == 0){
//       digitalWrite(LED, HIGH);    
//       flag = 1;
//     }  
//     else{
//       digitalWrite(LED, LOW);    
//       flag = 0;
//     }

     /* Imprime a hora no display serial */
     imprimeLCD();
   }
}


/******************************************************** 
 *  
 *  Demais funções do Sistema.
 *  
 ********************************************************/

void configTimer0(){
  /* Inicialmente eu faço o reset de todos os registradores. */
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCNT0  = 0x00;

  /********************************************************************* 
   * 1. Coloco o OCR0A como 125. Este valor em hexa é 0x7D.
   * 2 .Quero que haja o trabalho no formato CTC, que significa
   *    Clear Timer on Compare. Isso é feito setando 
   *    TCCR0A = 0x02.
   * 3. Para o preescale em 1024, tem de se fazer TCCR0B = 0x05.
   * 4. Além do mais, tenho de setar a máscara para funcionar de forma
   *    que  eu tenha interrupção quando ocorrer a interrupção
   *    por igualdade entre o TCNT0 com o OCR0A.             
   ********************************************************************/
  OCR0A  = 0x7D;
  TCCR0A = 0x02;
  TCCR0B = 0x05;
  TIMSK0 = 0x02;
}


void initTime(int _dia, int _hora, int _minuto, int _segundo){
  dia      = _dia;
  hora     = _hora;
  minuto   = _minuto;
  segundo  = _segundo;
}


void imprimeSerial(){
  int m;
  m = sprintf(stringHora, "%2d:%2d:%2d", hora, minuto, segundo);
  Serial.println(stringHora);
}


void imprimeLCD(){
  /* Limpa a tela */
  Display_LCD.clear();
  
  /* Posiciona o cursor na coluna 0, linha 0 */
  Display_LCD.setCursor(0, 0);
  Display_LCD.print("Dia: ");
  Display_LCD.print(dia);

  int m;

  /* Tocante -- HORA */
  if ( hora < 10 ){
    /* Tocante -- MINUTO */
    if ( minuto < 10 ){
      /* Tocante -- SEGUNDO */
      if (segundo < 10 ){
        m = sprintf(stringHora, "0%d:0%d:0%d", hora, minuto, segundo);
      }
      else {
        m = sprintf(stringHora, "0%d:0%d:%d", hora, minuto, segundo);
      }
    }
    else{
      if ( segundo < 10 ){
        m = sprintf(stringHora, "0%d:%d:0%d", hora, minuto, segundo);
      }
      else {
        m = sprintf(stringHora, "0%d:%d:%d", hora, minuto, segundo);
      }
    }
  }
  else {
    /* Tocante -- MINUTO */
    if ( minuto < 10 ){
      /* Tocante -- SEGUNDO */
      if (segundo < 10 ){
        m = sprintf(stringHora, "%d:0%d:0%d", hora, minuto, segundo);
      }
      else {
        m = sprintf(stringHora, "%d:0%d:%d", hora, minuto, segundo);
      }
    }
    else{
      if ( segundo < 10 ){
        m = sprintf(stringHora, "%d:%d:0%d", hora, minuto, segundo);
      }
      else {
        m = sprintf(stringHora, "%d:%d:%d", hora, minuto, segundo);
      }
    }
  }

  /* Posiciona o cursor na coluna 0, linha 1 */
  Display_LCD.setCursor(0, 1);
  Display_LCD.print(stringHora);    
}
