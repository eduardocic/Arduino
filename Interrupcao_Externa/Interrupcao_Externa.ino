static int cont = 0;
static int flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);

  /***************************************************** 
   * Caracterização do sistema para interrupção externa.
   * Importante dizer que isso fará a setagem do sistema 
   * de forma a que a gente tenha a INT0 (pino 2).    
   ****************************************************/
  EICRA = 0x03;
  EIMSK = 0x01;
}

void loop() {
}


ISR(INT0_vect){
  cont++;
  Serial.print("Interrupção: ");
  Serial.println(cont);
  if ( flag == 0 ){
    flag = 1;
  }
  else {
    flag = 0;
  }
}


