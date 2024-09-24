#include <OneWire.h>             // Inclui a biblioteca OneWire para comunicação com dispositivos OneWire
#include <DallasTemperature.h>   // Inclui a biblioteca DallasTemperature para sensores de temperatura

/**
 * Definições dos pinos para LEDs e buzzer:
 * - Pino para LED vermelho
 * - Pino para LED verde
 * - Pino para LED amarelo
 * - Pino para o buzzer (som)
 * - Canal PWM para o buzzer (som)
 * - Histerese de 2º C para controle de temperatura
 */
#define RED_LED 26
#define YELLOW_LED 27
#define GREEN_LED 32
#define BUZZER_PIN 5
#define PWM_CHANNEL 0
#define HISTERESE 2  

float temperaturaAnterior = 0.0; // Armazena a temperatura anterior

// Define o pino do barramento OneWire
#define ONE_WIRE_BUS 25 // Usando o GPIO 25

// Cria uma instância da classe OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Passa a instância oneWire para a biblioteca DallasTemperature
DallasTemperature sensors(&oneWire);

/**
 * @brief Configura os pinos e inicializa as bibliotecas.
 *
 * Esta função é chamada uma vez na inicialização do programa.
 * Define os pinos dos LEDs como saídas, configura o buzzer para
 * uso com PWM e inicializa a comunicação serial.
 */
void setup(void) {
    // Define os pinos de LED como saídas
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    ledcSetup(PWM_CHANNEL, 5000, 8); // Configuração inicial do PWM com frequência de 5000 Hz e 8 bits de resolução
    ledcAttachPin(BUZZER_PIN, PWM_CHANNEL); // Associa o pino do buzzer ao canal PWM

    sensors.begin(); // Inicializa a biblioteca DallasTemperature
    Serial.begin(9600); // Inicializa a comunicação serial a 9600 bps
}

/**
 * @brief Loop principal do programa.
 *
 * Esta função é chamada repetidamente após a configuração inicial.
 * Ela lê a temperatura dos sensores e controla os LEDs e o buzzer
 * com base em faixas de temperatura, além de exibir a temperatura
 * no monitor serial.
 */
void loop() {
    // Solicita a temperatura dos sensores
    sensors.requestTemperatures();
    float temperaturaAtual = sensors.getTempCByIndex(0); // Obtém a temperatura atual em graus Celsius

    // Exibe a temperatura no monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperaturaAtual);
    Serial.println(" Cº");

    // Controle de LEDs e buzzer baseado na temperatura
    if (temperaturaAtual > temperaturaAnterior) {
        Serial.println("A temperatura está SUBINDO.");
        Serial.println("Temperatura NORMAL (SEM histerese)");

        if (temperaturaAtual < 24.0) {
			
            // Se a temperatura for menor que 24ºC
            Serial.println("Acende LED VERDE");
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(150); // Espera 150 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(150); // Espera 150 ms
        } 
        else if (temperaturaAtual >= 24.0 && temperaturaAtual <= 29.0) {
			
            // Se a temperatura estiver entre 24ºC e 29ºC
            Serial.println("Acende LED AMARELO");
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(300); // Espera 300 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(300); // Espera 300 ms
        } 
        else {
			
            // Se a temperatura for maior que 29ºC
            Serial.println("Acende LED VERMELHO");
            digitalWrite(RED_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(600); // Espera 600 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(600); // Espera 600 ms
        }
    } 
    else {
        Serial.println("A temperatura está DESCENDO.");
        Serial.println("IDENTIFICA HISTERESE");

        if (temperaturaAtual < (24.0 - HISTERESE)) {
			
            // Se a temperatura for menor que 22ºC
            Serial.println("Acende LED VERDE");
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(150); // Espera 150 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(150); // Espera 150 ms
        } 
        else if (temperaturaAtual >= (24.0 - HISTERESE) && temperaturaAtual <= (29.0 - HISTERESE)) {
			
            // Se a temperatura estiver entre 22ºC e 27ºC
            Serial.println("Acende LED AMARELO");
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(300); // Espera 300 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(300); // Espera 300 ms
        } 
        else {
			
            // Se a temperatura for maior que 27ºC
            Serial.println("Acende LED VERMELHO");
            digitalWrite(RED_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);

            // Toca uma frequência de 440Hz no canal PWM
            ledcWriteTone(PWM_CHANNEL, 440);
            delay(600); // Espera 600 ms
            ledcWriteTone(PWM_CHANNEL, 0); // Para o som
            delay(600); // Espera 600 ms
        }
    }  

    // Atualiza a temperatura anterior
    temperaturaAnterior = temperaturaAtual;
}
