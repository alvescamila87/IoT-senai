
#define RED_LED 32
#define DEBUG_MODE

void setup() {
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
  #ifdef DEBUG_MODE
  Serial.println("Modo de ativação de DEBUG");
  #endif
}

void loop() {
  
  for(int i = 0; i < 3; i++) {
    #ifdef DEBUG_MODE
    Serial.println("Acende LED");
    #endif
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    #ifdef DEBUG_MODE
    Serial.println("Desliga LED");
    #endif
    delay(1000);    
  }

  #ifdef DEBUG_MODE
  Serial.println("Reinicia ciclo: aguarda 5s - LED apagado");
  #endif  
  delay(5000);

}
