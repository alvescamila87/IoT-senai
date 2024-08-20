
#define RED_LED 32
#define DEBUG_MODE
int i = 1;

void setup() {
  pinMode(RED_LED, OUTPUT);
  
  Serial.begin(9600);
  #ifdef DEBUG_MODE
  Serial.println("Modo de ativação de DEBUG");
  #endif
}

void loop() {
  
  if(i < 4) {

  #ifdef DEBUG_MODE
  Serial.print(i);
  Serial.println("ª vez Acende LED");
  #endif 
  digitalWrite(RED_LED, HIGH);
  delay(1000);

  #ifdef DEBUG_MODE
  Serial.print(i);
  Serial.println("ª vez Desliga LED");
  #endif 
  digitalWrite(RED_LED, LOW);
  delay(1000);

  i++;

  } else if (i == 4) {
    #ifdef DEBUG_MODE
    Serial.print(i);
    Serial.println("ª vez - 4º vez Acende LED: 2s");
    #endif 
    digitalWrite(RED_LED, HIGH);
    delay(2000);

    #ifdef DEBUG_MODE
    Serial.print(i);
    Serial.println("ª vez - 4º vez  Desliga LED: 8s");
    #endif 
    digitalWrite(RED_LED, LOW);
    delay(8000);

    i++;
    
  } else {
    #ifdef DEBUG_MODE
    Serial.println("Reinicia ciclo: aguarda 5s - LED apagado");
    #endif  
    delay(5000);
    i = 1;
  }

}
