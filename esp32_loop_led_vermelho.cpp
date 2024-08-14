
#define RED_LED 32
#define DEBUG_MODE
int i = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  
  Serial.begin(9600);
  #ifdef DEBUG_MODE
  Serial.println("Modo de ativação de DEBUG");
  #endif
}

void loop() {
  #ifdef DEBUG_MODE
  Serial.println("Acende LED");
  #endif 
  digitalWrite(RED_LED, HIGH);
  delay(1000);

  #ifdef DEBUG_MODE
  Serial.println("Desliga LED");
  #endif 
  digitalWrite(RED_LED, LOW);
  delay(1000);

  i++;

  if(i == 3){
    #ifdef DEBUG_MODE
    Serial.println("Reinicia ciclo: aguarda 5s - LED apagado");
    #endif  
    delay(5000);
    i = 0;
  }

}
