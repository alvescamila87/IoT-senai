/*
* ESP32: utilizando estrutura WHILE no wokwi
*/

#define LED_VERMELHO 32
#define DEBUG_MODE //'modo DEV', comentar essa linha, caso não quiser debug

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  Serial.begin(9600);

  #ifdef DEBUG_MODE
  Serial.println("Modo de depuração ativação");
  #endif
}

void loop() {
  int i = 0;

  while(i < 3) {
    digitalWrite(LED_VERMELHO, HIGH);
    #ifdef DEBUG_MODE
    Serial.println("Acende LED");
    #endif
    delay(1000);
    digitalWrite(LED_VERMELHO, LOW);
    #ifdef DEBUG_MODE
    Serial.println("Apaga LED");
    #endif
    delay(1000);
    i = i + 1;
  }
  
  #ifdef DEBUG_MODE
  Serial.println("Apaga LED e aguarda 5 segundos para novo ciclo");
  #endif
  delay(5000);
  
}
