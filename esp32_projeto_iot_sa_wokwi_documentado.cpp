/*
 * PROJETO SENAI/SC S.A: IoT Sensores
 *
 * Descrição geral do código:
 * Este código é um sistema de monitoramento e envio de dados de sensores ambientais (temperatura, distância e turbidez) para um broker MQTT. 
 * Ele utiliza um ESP32 para se conectar a uma rede Wi-Fi, obter dados dos sensores e publicar os resultados em um tópico MQTT. 
 * O código é responsável por coletar dados de temperatura, distância e turbidez da água e enviar esses dados periodicamente a um broker MQTT.
 * 
 * Objetivo do projeto:
 * O objetivo é fornecer uma solução para monitoramento remoto da qualidade da água, coletando dados de diferentes sensores e transmitindo-os em tempo real.
 * 
 * Autores: Camila Alves, Davi Galvão, João C. Emídio.
 * Data de criação: 26/11/2024
 */

/*
* 1. CONFIGURAÇÃO INICIAL 
* Portas dos ESP32 utilizadas pelos sensores, bem como as variáveis necessárias para ler os valores.
*/ 
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 18 // usando o GPIO 18
#define PORTA_DISTANCIA_TRIG 4 // sensor de distância HCSR04 GPIO 4
#define PORTA_DISTANCIA_ECHO 2 // sensor de distância HCSR04 GPIO 2
#define PORTA_TURBIDEZ_DAC 35 // sensor de turbidez GPIO 35
#define QUANTIDADE_AMOSTRAS 10 // sensor de turbidez - NÚMERO LEITURA PARA FAZER A MÉDIA

OneWire oneWire(ONE_WIRE_BUS); // Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire
DallasTemperature sensors(&oneWire); // Passa uma referência oneWire para a biblioteca DallasTemperature - WOKWI

float temperature = 0.00; // variável que recebe do sensor a temperatura
int NTU = 0; // variável que recebe do sensor a turbidez
float distancia=0.0; // variável que recebe do sensor a distância
int iSensor=0; // controla qual sensor terá seus dados enviados para o broker

//const char* ntpServer = "pool.ntp.org"; // o endereço do servidor NTP que será usado para obter a hora local.
const char* ntpServer = "br.pool.ntp.org"; // o endereço do servidor NTP que será usado para obter a hora local.

const long  gmtOffset_sec = -3 * 3600;  // Ajuste para o seu fuso horário (exemplo: -3 horas)
const int   daylightOffset_sec = 0;     // Não há ajuste para o horário de

// Configurações de Wi-Fi
const char* ssid = "ABC";
const char* password = "12345678";

// Configurações do MQTT (utilize um dos endpointes abaixo
//const char* mqtt_server = "broker.hivemq.com";       // Endereço público do broker hivemq
const char* mqtt_server = "test.mosquitto.org";      // Endereço do broker mosquitto
const int mqtt_port = 1883;                         // porta do broker
const char* mqtt_topic = "le_dados_qualidade_agua_grupo_b"; // nome do topico
WiFiClient espClient; // cria uma instância da classe WiFiClient que é da biblioteca Wifi

/*
* Construtor de PubSubClient recebe como argumento espCliente, isso
* cria uma associação entre o cliente MQTT (client) e o 
* cliente Wi-Fi (espClient), de modo que o cliente MQTT possa usar a 
* conexão Wi-Fi gerenciada pelo espClient.
*/
PubSubClient client(espClient); 

unsigned long lastMillis = 0;
const unsigned long intervaloLeitura = 15000; // Intervalo entre leituras (15 segundos)

/*
 * Função: setup_wifi
 * Descrição: Esta função configura e realiza a conexão com uma rede Wi-Fi utilizando as credenciais fornecidas.
 * Ela tenta se conectar ao Wi-Fi por até 10 segundos e, em caso de falha, reinicia o dispositivo.
 * Parâmetros: Nenhum
 * Retorno: Nenhum
 */
void setup_wifi() {
  espClient.setTimeout(15000); // Define um timeout de 15 segundos para a operação de conexão MQTT (conexão tcp)
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {  // Timeout de 10 segundos
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());

    // Inicializa o NTP server
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  } else {
    Serial.println("Falha ao conectar ao WiFi, reiniciando o dispositivo...");
    delay(1000);
    ESP.restart(); // Reinicia o ESP32
  }
}

/*
 * Função: reconnect
 * Descrição: Esta função tenta reconectar ao broker MQTT. Se a conexão falhar, ela tentará reconectar a cada 10 segundos.
 * Parâmetros: Nenhum
 * Retorno: Nenhum
 */
void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando conectar ao broker MQTT..." + String(mqtt_server));
    if (client.connect("")) {
      Serial.println("Conectado ao broker MQTT");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 10 segundos");
      delay(10000);
    }
  }
}

/*
 * Função: publicarDadosMQTT
 * Descrição: Esta função publica os dados de leitura no broker MQTT. Se o cliente não estiver conectado, ela tenta reconectar.
 * Parâmetros: 
 * - dadosJson (String): Os dados a serem publicados, formatados como uma string JSON.
 * Retorno: Nenhum
 */
void publicarDadosMQTT(String dadosJson) {
  if (client.connected()) {
    if (client.publish(mqtt_topic, dadosJson.c_str())) {
      Serial.println("Mensagem publicada com sucesso!");
    } else {
      Serial.println("Falha na publicação da mensagem.");
    }
  } else {
    Serial.println("Cliente MQTT desconectado, tentando reconectar...");
    reconnect();
  }
}

/*
 * Função: lerEPublicarDados
 * Descrição: Esta função coleta os dados dos sensores de temperatura, distância e turbidez, monta um objeto JSON com os dados e chama 
 * a função de publicação MQTT para enviar esses dados. 
 * Parâmetros:
 * - iSensor (int): Um índice que define qual sensor será lido (0 - distância, 1 - temperatura, 2 - turbidez).
 * Retorno: Nenhum
 */
void lerEPublicarDados(int iSensor) {
  struct tm timeinfo;
  
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter o tempo");
    return;
  }

  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);

  /*
    ESTA PARTE DO CODIGO MONTA O JSON QUE SERÁ O PARAMETRO
    DE ENTRADA PARA A FUNCAO publicarDadosMQTT()
  */

  DynamicJsonDocument dados(256); // cria um objeto DynamicJsonDocument chamado dados com um tamanho inicial de 1024 bytes.

  switch (iSensor) {
    case 0: 
      dados[0]["variable"] = "valor_distancia";
      dados[0]["unit"] = "cm";
      dados[0]["value"] = String(distancia);
      break;

    case 1:
      dados[0]["variable"] = "valor_temperatura";
      dados[0]["unit"] = "oC";
      dados[0]["value"] = String(temperature);
      break;

    case 2:
      dados[0]["variable"] = "valor_turbidez";
      dados[0]["unit"] = "NTU";
      dados[0]["value"] = String(NTU);
      break;

    default:
      Serial.println("Valor de iSensor fora do esperado");
      break;
  }

  dados[0]["timestamp"] = timeStringBuff;

  String dadosJson;
  serializeJson(dados, dadosJson);

  Serial.println("Publicando a leitura dos sensores de qualidade da água...");
  Serial.println(dadosJson);

  publicarDadosMQTT(dadosJson); // Publica os dados no broker MQTT
}

/*
 * Função: checkWiFi
 * Descrição: Esta função verifica se o dispositivo está conectado à rede Wi-Fi. Se não estiver, tenta reconectar.
 * Parâmetros: Nenhum
 * Retorno: Nenhum
 */
void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado, tentando reconectar...");
    setup_wifi();  
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi(); // Configura a conexão Wi-Fi
  sensors.begin(); // Inicia a biblioteca
  analogReadResolution(10); // seta resolução conversor AD para 10 bits 
  
  client.setServer(mqtt_server, mqtt_port);
  
  pinMode(PORTA_DISTANCIA_TRIG, OUTPUT);
  pinMode(PORTA_DISTANCIA_ECHO, INPUT);
}

void loop() {
  checkWiFi(); // Verifica e reconecta ao Wi-Fi se necessário

  if (!client.connected()) {
    reconnect();  // Reconecta ao broker MQTT se a conexão cair
  }
  
  client.loop(); // Mantém a conexão MQTT ativa 
  
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= intervaloLeitura) {
    lastMillis = currentMillis;
    lerEPublicarDados(iSensor);

    iSensor++;
    if (iSensor > 2) {
      iSensor = 0;
    }
    
    // 1. SENSOR DISTÂNCIA (Sensor HC-SR04)
    digitalWrite(PORTA_DISTANCIA_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PORTA_DISTANCIA_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PORTA_DISTANCIA_TRIG, LOW);
    distancia = (pulseIn(PORTA_DISTANCIA_ECHO, HIGH) * 0.0343) / 2;
    Serial.print("Distância atual: ");
    Serial.println(distancia);

    // 2. SENSOR TEMPERATURA (Sensor DS-18B20)
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    Serial.print("Temperatura atual: ");
    Serial.print(temperature);
    Serial.println(" ºC");

    // 3. SENSOR TURBIDEZ (Sensor ST-100) 
    int analogValue = 0;
    int somaAnalogValue = 0;
    for (int i = 0; i < 9; i++) {
      analogValue = analogRead(PORTA_TURBIDEZ_DAC);
      somaAnalogValue += analogValue;
      delay(10);
    }

    analogValue = somaAnalogValue / QUANTIDADE_AMOSTRAS;
    Serial.print("Valor médio obtido turbidez: ");
    Serial.println(analogValue);

    NTU = -0.012144 * analogValue * analogValue + 0.90066 * analogValue + 2995.8;
    Serial.print("Turbidez atual (NTU): ");
    Serial.println(NTU);
    delay(1500);
  }
}
