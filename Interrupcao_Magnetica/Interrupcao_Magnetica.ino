static int cont = 0;
static int flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);

  /********************************************************* 
   * Caracterização do sistema para interrupção externa.
   * Importante dizer que isso fará a setagem do sistema 
   * de forma a que a gente tenha a INT0 (pino 2).    
   * 
   * Olhando mais atentamento o registrador EICRA, per-
   * cebe-se que para ativar a interrupção por INT0 
   * quando na borda de descida, temos meio que zerar 
   * a INT1 e ativar a INT0 de borda de descida. 
   * 
   * Isso é feito tomando os bits:
   * ISC11 = '0'
   * ISC10 = '0'
   * ISC01 = '0'
   * ISC00 = '0'
   * 
   * Ademais, Para ativarmos a interrupção 1, é importante
   * olhar para a máscara EIMSK. Conforme está escrito
   * abaixo.
   ********************************************************/
  EICRA = 0x01;
  EIMSK = 0x01;
}

void loop() {
}


ISR(INT0_vect){
//  cont++;
//  Serial.print("Interrupção: ");
//  Serial.println(cont);
  if (flag == 0){
    cont++;
    Serial.println(cont);
    flag = 1;
  }
  if (flag == 1){
    flag = 0;
  }
  
}

