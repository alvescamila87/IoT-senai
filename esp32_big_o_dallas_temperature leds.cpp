#include <OneWire.h>
#include <DallasTemperature.h>

#define RED_LED 32
#define YELLOW_LED 33
#define GREEN_LED 18

// O fio de dados é conectado no GPIO do ESP32
#define ONE_WIRE_BUS 4 // usando o GPIO 4

// Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire
OneWire oneWire(ONE_WIRE_BUS);

// Passa uma referência oneWire para a biblioteca DallasTemperature
DallasTemperature sensors(&oneWire);

void setup(void)
{
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    sensors.begin();  // Inicia a biblioteca
    Serial.begin(9600);
}

void loop(void)
{

   float temperature = leTemperatura();


    // Exibe a temperatura em Celsius
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" ºC");

    // Controla os LEDs baseado na temperatura
    if (temperature <= 15.0) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    } 
    else if (temperature > 15.0 && temperature <= 25.0) {

        Serial.println("entra no amarelo");
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
   
    }
    else {
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, HIGH);
    }  

    delay(1500); // Pausa de 1,5 segundos
}


float leTemperatura()
{
  float temperatura = 16.00;

  //Manda comando para ler temperaturas
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);

  //return temperatura;
}