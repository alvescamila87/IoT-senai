/*
 CRIE UM HEADER PARA ESTE CODIGO DE ACORDO COM AS INSTRUCOES ABAIXO:

 Criar um header de documentação para cada função:

 a) Utilize comentários início de cada função.
 b) Descreva o que cada função faz de maneira clara e concisa.
 c) Detalhe os parâmetros (nome e tipo) e explique a finalidade de cada um.
 d) Indique o tipo de valor retornado pela função e descreva seu significado.
 e) Incluir uma descrição geral do código:

 No topo do arquivo, escreva um comentário que explique o propósito geral do código e a funcionalidade que ele oferece.
 
 Inclua também informações sobre o autor, a data de criação, e uma breve introdução ao funcionamento geral do código.
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <OneWire.h>
#include <DallasTemperature.h>

 
// == AQUI VOCÊ DEVERÁ  INCLUIR AS PORTAS DOS ESP32 UTILIZADA PELOS SENSORES
//    BEM COMO AS VARIAVEIS NECESSARIAS PARA LER OS VALORES, NENHUMA VARIAVEL
//    DE SENSORES DEVEM SER DECLARADA NO LOOP OU NO SETUP  == 

// 1. Declarão de todos os sensores

// O fio de dados é conectado no GPIO do ESP32
#define ONE_WIRE_BUS 18 // usando o GPIO 18
// Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire
OneWire oneWire(ONE_WIRE_BUS);
#define PORTA_DISTANCIA_TRIG 4 // sensor de distância HCSR04 GPIO 4
#define PORTA_DISTANCIA_ECHO 2 // sensor de distância HCSR04 GPIO 2
#define PORTA_TURBIDEZ_DAC 35 // sensor de turbidez GPIO 35
#define QUANTIDADE_AMOSTRAS 10 // sensor de turbidez - NÚMERO LEITURA PARA FAZER A MÉDIA

float temperature = 0.0;
int NTU = 0;

// 1.1 Passa uma referência oneWire para a biblioteca DallasTemperature - WOKWI
DallasTemperature sensors(&oneWire);

float distancia=0.0;

// controla qual sensor terá seus dados enviados para o broker
int iSensor=0;

// incluir AQUI as variáveis necessarias para os valores de leitura para
// os outros sensores

const char* ntpServer = "pool.ntp.org"; // o endereço do servidor NTP que será usado para obter a hora local.
const long  gmtOffset_sec = -3 * 3600;  // Ajuste para o seu fuso horário (exemplo: -3 horas)
const int   daylightOffset_sec = 0;     // Não há ajuste para o horário de

// Configurações de Wi-Fi
const char* ssid = "ABC";
const char* password = "12345678";

// Configurações do MQTT (utilize um dos endpointes abaixo

//const char* mqtt_server = "broker.hivemq.com";       // Endereço público do broker hivemq
  const char* mqtt_server = "test.mosquitto.org";      // Endereço do broker mosquitto

const int mqtt_port = 1883;                         // porta do broker

/*  == ATENCAO == AQUI É IMPORTANTE MUDAR O NOME DO TOPICO PARA CADA EQUIPE
 *  SENÃO O QUE VAI ACONTECER? TODAS AS EQUIPES VAO PUBLICAR NO **MESMO TOPICO**
 *  Sugestão: mude o nome do topico para por exemplo "le_dados_qualidade_agua_equipe_A" ou
 *  qualquer outro nome, importante é se assegurar que o nome é unico e só vocês estão utilizando
 */

const char* mqtt_topic = "le_dados_qualidade_agua_grupo_b"; // nome do topico

// cria uma instância da classe WiFiClient que é da biblioteca Wifi
WiFiClient espClient; 

/* Construtor de PubSubClient recebe como argumento espCliente, isso
   cria uma associação entre o cliente MQTT (client) e o 
   cliente Wi-Fi (espClient), de modo que o cliente MQTT possa usar a 
   conexão Wi-Fi gerenciada pelo espClient.
*/
PubSubClient client(espClient); 

unsigned long lastMillis = 0;
const unsigned long intervaloLeitura = 15000; // Intervalo entre leituras (15 segundos)

// Função de conexão Wi-Fi com timeout e reinicialização forçada
void setup_wifi() {

  // Define um timeout de 15 segundos para a operação de conexão MQTT (conexão tcp)
  espClient.setTimeout(15000); 
   
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
    delay(1000);  // Pequena pausa antes de reiniciar
    ESP.restart();  // Reinicia o ESP32
  }
}

// Função de reconexão ao broker MQTT
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

// Função para publicar dados no broker MQTT
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

// Preparar os dados para publicação
void lerEPublicarDados(int iSensor) {
  
  /*
    Declara uma variável timeinfo do tipo struct tm, que é uma estrutura padrão da biblioteca time.h 
    utilizada para armazenar informações sobre uma data e hora específica.
  */
  
  struct tm timeinfo;
  
  // Obtem o tempo local atual
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter o tempo");
    return;
  }

  /* 
  declara um array de caracteres chamado timeStringBuff com tamanho 50, 
  que será usado para armazenar a string de data e hora formatada
  */
  char timeStringBuff[50];

  /*
   Chama a função strftime(), que é uma função padrão da biblioteca C 
   para converter informações de data e hora em uma string formatada.
   */
  
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);

  /*
    == ESTA PARTE DO CODIGO MONTA O JSON QUE SERÁ O PARAMETRO
    DE ENTRADA PARA A FUNCAO publicarDadosMQTT() ==
  */

  // cria um objeto DynamicJsonDocument chamado dados com um tamanho inicial de 1024 bytes.
  DynamicJsonDocument dados(256);

  switch (iSensor) {
    case 0:

      /*  ==ATENCAO aqui adicionar JSON sensor de distancia */
      /*
      Essa linha define o valor da chave "variable" no primeiro elemento do documento JSON (índice 0) 
      com a string "valor_distancia".
      */
      dados[0]["variable"] = "valor_distancia";
      /*
      Essa linha define o valor da chave "unit" no primeiro elemento do documento JSON (índice 0) 
      com  a string "cm".
       */
      dados[0]["unit"] = "cm";
      /*
      Essa linha define o valor da chave "value" no primeiro elemento do documento JSON com  
      uma string criada a partir do valor da variável distancia.
      */
      dados[0]["value"] = String(distancia);
      /*
      Essa linha define o valor da chave "timestamp" no primeiro elemento do documento JSON 
      com a string armazenada em timeStringBuff.
      */
      break;

    case 1:
    
      /* ==ATENCAO aqui adicionar JSON sensor de temperatura */

            /*
      Essa linha define o valor da chave "variable" no primeiro elemento do documento JSON (índice 1) 
      com a string "valor_distancia".
      */

      // float temperature = 0.0;

      // // Leitura da temperatura
      // sensors.requestTemperatures();
      // temperature = sensors.getTempCByIndex(0);

      dados[0]["variable"] = "valor_temperatura";
      /*
      Essa linha define o valor da chave "unit" no primeiro elemento do documento JSON (índice 1) 
      com  a string "oC".
       */
      dados[0]["unit"] = "oC";
      /*
      Essa linha define o valor da chave "value" no primeiro elemento do documento JSON com  
      uma string criada a partir do valor da variável temperature.
      */
      dados[0]["value"] = String(temperature);
      /*
      Essa linha define o valor da chave "timestamp" no primeiro elemento do documento JSON 
      com a string armazenada em timeStringBuff.
      */
      
      break;

    case 2:
      /*  ==ATENCAO aqui adicionar JSON sensor de turbidez */

            /*
      Essa linha define o valor da chave "variable" no primeiro elemento do documento JSON (índice 2) 
      com a string "valor_turbidez".
      */

      // int NTU = 0;

      dados[0]["variable"] = "valor_turbidez";
      /*
      Essa linha define o valor da chave "unit" no primeiro elemento do documento JSON (índice 2) 
      com  a string "NTU".
       */
      dados[0]["unit"] = "NTU";
      /*
      Essa linha define o valor da chave "value" no primeiro elemento do documento JSON com  
      uma string criada a partir do valor da variável turbidez.
      */
      dados[0]["value"] = String(NTU);
      /*
      Essa linha define o valor da chave "timestamp" no primeiro elemento do documento JSON 
      com a string armazenada em timeStringBuff.
      */

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

  // Publica os dados no broker MQTT
  publicarDadosMQTT(dadosJson);
}

// Função para verificar e reconectar o Wi-Fi se necessário
void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado, tentando reconectar...");
    setup_wifi();
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();  // Configura a conexão Wi-Fi
  
  sensors.begin();  // 1. Inicia a biblioteca

  analogReadResolution(10); // seta resolução conversor AD para 10 bits + // 1. sensor turbidez
  
  // Define o servidor MQTT apenas uma vez no setup
  client.setServer(mqtt_server, mqtt_port);  

  //   == AQUI VOCÊ DEVERÁ INCLUIR AS CONFIGURAÇÕES NECESSÁRIAS PARA CADA SENSOR ==
  // configura pinos do sensor HC-SR04
  pinMode(PORTA_DISTANCIA_TRIG, OUTPUT); // Configura o pino TRIG como saída
  pinMode(PORTA_DISTANCIA_ECHO, INPUT);  // Configura o pino ECHO como entrada
  //pinMode(PINO_LED, OUTPUT);  // Configura o pino LED como saída

  /*  == ATENCAO ==
   *   incluir AQUI a configuração de portas (caso necessario) para os outros sensores
   */

}

void loop() {
  checkWiFi();  // Verifica e reconecta ao Wi-Fi se necessário
  
  if (!client.connected()) {
    reconnect();  // Reconecta ao broker MQTT se a conexão cair
  }
  
  client.loop();  // Mantém a conexão MQTT ativa                           

  // Verifica se está na hora de fazer uma nova leitura
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= intervaloLeitura) {
    lastMillis = currentMillis;
    lerEPublicarDados(iSensor);  // Executa a leitura e publicação dos dados

    // rotaciona qual sensor irá ter seus valores publicados
    iSensor++;
    if(iSensor > 2)    {
      iSensor=0; // rotativo, volta para o 1o sensor.
    }
	
	
	  // == AQUI DEVE SER EXECUTADO AO CODIGO RELATIVO LEITURA DOS LEITORES ==

	  // le distância do sensor HC-SR04
	  digitalWrite(PORTA_DISTANCIA_TRIG, LOW);
	  delayMicroseconds(2);
	  digitalWrite(PORTA_DISTANCIA_TRIG, HIGH);
	  delayMicroseconds(10);
	  digitalWrite(PORTA_DISTANCIA_TRIG, LOW);
	  distancia = (pulseIn(PORTA_DISTANCIA_ECHO, HIGH)*0.0343); // distancia em cm
    Serial.println("Valor distância atual: ");
    Serial.print(distancia);

	  //distancia = random(4, 401);  // VALOR DUMMY PARA TESTES, ESTA LINHA DEVE SER REMOVIDA QUANDO USAR O ESP32
	  
	  // 2. SENSOR TEMPERATURA
    //float temperature = leTemperatura(); - WOKWI
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    // Exibe a temperatura em Celsius
    Serial.println("Temperatura atual: ");
    Serial.print(temperature);
    Serial.println(" ºC");

    // 2. SENSOR TURBIDEZ
    int analogValue=0;
    int i=0;
    int somaAnalogValue=0;

    for (i = 0; i < 9; i++)    {
    // Read the analog value from GPIO 35 0...1023
    analogValue = analogRead(PORTA_TURBIDEZ_DAC);
    somaAnalogValue += analogValue; // soma valores
    delay(10);
    }

    // 3. SENSOR TURBIDEZ  
    analogValue = somaAnalogValue/QUANTIDADE_AMOSTRAS; // valor médio
    Serial.print("Valor médio obtido turbudez: ");
    Serial.println(analogValue);
    // Add a delay to slow down the output in the Serial Monitor

    // Valor NTU
    NTU = -0.012144*analogValue*analogValue + 0.90066*analogValue + 2995.8;
    Serial.print("Valor em NTU atual: ");
    Serial.println(NTU);
    delay(1500); 
	
  }

}
   

  /*  == ATENCAO ==
   *  incluir AQUI a leitura dos outros sensores  
   *  
   */
   
   // 2. SENSOR TEMPERATURA - OPCIONAL
//float leTemperatura()
//{
  //float temperatura = 16.00;

  //Manda comando para ler temperaturas
  //sensors.requestTemperatures();
  //return sensors.getTempCByIndex(0);

  //return temperatura;
//}
  

