
/**********************************************************************
 * Nome: Eduardo H. Santos
 * Data: 06 de Setembro 2018
 * 
 * 
 * Resumo: 
 *    
 *    Apresentará as informações de dia, data, hora e segundo no display
 * 
 **********************************************************************/
#include <LiquidCrystal.h>



/**********************************************************************
 * 
 * Protótipo de função
 * 
 **********************************************************************/
void imprime_LCD();

/* Fazer os ajustes necessários em termos de conexão */
LiquidCrystal Display_LCD(12, 11, 5, 4, 3, 2);

static char stringHora[10];
 
void setup()
{
  /* Display de 16 colunas e 2 linhas */
  Display_LCD.begin(16, 2);
}


 
void loop()
{
  
}


void imprime_LCD(){

  /* Limpa a tela */
  Display_LCD.clear();
  
  /* Posiciona o cursor na coluna 0, linha 0 */
  Display_LCD.setCursor(0, 0);
  Display_LCD.print("Dia: ");
  Display_LCD.print(dia);

  int m;
  m = sprintf(stringHora, "%2d:%2d:%2d", hora, minuto, segundo);
    /* Posiciona o cursor na coluna 0, linha 1 */
  Display_LCD.setCursor(0, 1);
  Display_LCD.print(stringHora);    
}



