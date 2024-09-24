#include <OneWire.h>
#include <DallasTemperature.h>

#define RED_LED 26
#define YELLOW_LED 27
#define GREEN_LED 32
#define buzzerPin 5
#define pwmChannel 0
#define histerese 2 // histerese 2º C

// O fio de dados é conectado no GPIO do ESP32
#define ONE_WIRE_BUS 4 // usando o GPIO 4

// Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire
OneWire oneWire(ONE_WIRE_BUS);

// Passa uma referência oneWire para a biblioteca DallasTemperature
DallasTemperature sensors(&oneWire);

void setup(void) {

pinMode(RED_LED, OUTPUT);
pinMode(YELLOW_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);

ledcSetup(pwmChannel, 5000, 8); 
// setup inicial, a 
//frequencia é uma frequência dummy

// associa o pino 5 ao chanal 0 PWM
ledcAttachPin(buzzerPin, pwmChannel);

sensors.begin(); // inicia biblioteca
Serial.begin(9600);


}

void loop() {

// chama função temperatura
//float temperature = checaTemperatura();

sensors.requestTemperatures();
float temperature = sensors.getTempCByIndex(0);


// exibe temperatura em Cº
Serial.print("Temperatura: ");
Serial.print(temperature);
Serial.println(" Cº");

// controle de LEDs baseado na temperatura
if(temperature < (24.0 - histerese)) {

  Serial.println("Acende LED VERDE");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  //Toca uma frequência de 440Hz no chanal 0
  ledcWriteTone(pwmChannel, 440); //
  delay(150); // espera de 150 ms

  // Para o som
  ledcWriteTone(pwmChannel, 0);
  delay(150); // espera de 150 ms

} else if (temperature >= (24.0 - histerese) && temperature <= (29.0 - histerese)) {

  Serial.println("Acende LED AMARELO");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  //Toca uma frequência de 440Hz no chanal 0
  ledcWriteTone(pwmChannel, 440); //
  delay(300); // espera de 300 ms

  // Para o som
  ledcWriteTone(pwmChannel, 0);
  delay(300); // espera de 300 ms

} else {

  Serial.println("Acende LED VERMELHO");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  //Toca uma frequência de 440Hz no chanal 0
  ledcWriteTone(pwmChannel, 440); //
  delay(600); // espera de 600 ms

  // Para o som
  ledcWriteTone(pwmChannel, 0);
  delay(600); // espera de 600 ms

}

}

float checaTemperatura() {

  //float temperatura = 23;
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);

  //return temperatura;

}

