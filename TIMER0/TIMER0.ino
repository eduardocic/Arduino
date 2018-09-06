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
 ********************************************************/

#define LED 13

/********************************************************
 * 
 *  Variáveis utilizadas no meu sistema.
 *  
 *  Definirei as variáveis como estáticas
 *  apesar de serem globais
 *  
 ********************************************************/
static int cont    = 0;
static int segundo = 0;
static int minuto  = 0;
static int hora    = 0;
static int dia     = 0;

int flag = 0;
char stringHora[10];

/******************************************************** 
 *  
 *  Protótipo das funções.
 *  
 ********************************************************/
void initTime(int _hora, int _minuto, int _segundo);
void configTimer0();
void printa();


/******************************************************** 
 *  
 *  Função 'setup'
 *  
 ********************************************************/
void setup() {
  pinMode(LED, OUTPUT);
  
  configTimer0();
  initTime(23, 59, 45);
  
  Serial.begin(9600);
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
   // Atualizado a cada 0,008s.
   cont++;

   // Este evendo acontece apenas quando se completa 1s.
   if(cont == 125){
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
     
     // Alerta por LED para acompanhamento da atividade.
     if (flag == 0){
       digitalWrite(LED, HIGH);    
       flag = 1;
     }  
     else{
       digitalWrite(LED, LOW);    
       flag = 0;
     }

     printa();
   }
}


void initTime(int _hora, int _minuto, int _segundo){
  dia      = 0;
  hora     = _hora;
  minuto   = _minuto;
  segundo  = _segundo;
}


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


void printa(){
  int m;
  m = sprintf(stringHora, "%2d:%2d:%2d", hora, minuto, segundo);
  Serial.println(stringHora);
//  Serial.print(hora);
//  Serial.print(":");
//  Serial.print(minuto);
//  Serial.print(":");
//  Serial.println(segundo);
}

