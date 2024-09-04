/*
  Autor: Giovanni Rozza
  Data: 26 de agosto de 2024

  Descrição: 
  Este código se conecta a uma rede Wi-Fi usando um ESP32 e faz uma requisição HTTP GET 
  para obter informações sobre um país específico, utilizando a API pública do site 
  restcountries.com. O código realiza o parsing da resposta JSON utilizando a biblioteca ArduinoJson, 
  e então exibe no console serial o nome comum e oficial do país, 
  bem como os nomes nativos em diferentes idiomas, caso existam.

  Funcionalidade:
  - Conectar-se a uma rede Wi-Fi.
  - Realizar uma requisição HTTP GET para um servidor especificado.
  - Parsear a resposta JSON.
  - Exibir os nomes comuns e oficiais do país, bem como os nomes nativos em diferentes idiomas, no console serial.

  Funções:
  - void setup(): Configura a conexão Wi-Fi e realiza a requisição HTTP. Parseia e exibe os dados JSON retornados.
  - void loop(): Mantém o programa rodando, mas não é necessário realizar ações neste contexto específico.

  Dependências:
  - WiFi.h: Biblioteca para controle do módulo Wi-Fi do ESP32.
  - HTTPClient.h: Biblioteca para realizar requisições HTTP.
  - ArduinoJson.h: Biblioteca para manipulação e parsing de JSON.

  URLs:
  - https://restcountries.com/
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "https://restcountries.com/v3.1/name/swiss";
//const char* serverName = "https://restcountries.com/v3.1/name/france";

void setup() {
  Serial.begin(115200);
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Faz a requisição HTTP
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName);

    http.begin(url.c_str());
    int httpResponseCode = http.GET();

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    Serial.println();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      
      // Parseia o JSON
      DynamicJsonDocument doc(5000);
      deserializeJson(doc, payload);
      
      // Check if doc is an array
      if (doc.is<JsonArray>()) {

        JsonArray array = doc.as<JsonArray>();

        // Iterate through the array using index
        for (size_t i = 0; i < array.size(); i++) {
          
          JsonObject country = array[i].as<JsonObject>();

          const char* region = country["region"];
          const char* subregion = country["subregion"];

          // Print the extracted values
          Serial.print("Region: ");
          Serial.println(region);
          Serial.print("Subregion: ");
          Serial.println(subregion);
          Serial.println(); // Print a blank line for readability
        }

        Serial.print("Languages 1: \n");

        // Iterate through the array using index
        for (size_t i = 0; i < array.size(); i++) {
          
          JsonObject languages = array[i].as<JsonObject>();

          const char* fra = languages["languages"]["fra"];
          const char* gsw = languages["languages"]["gsw"];
          const char* ita = languages["languages"]["ita"];
          const char* roh = languages["languages"]["roh"];

          // Print the extracted values
          Serial.print("fra: ");
          Serial.println(fra);
          Serial.print("gsw: ");
          Serial.println(gsw);
          Serial.print("ita: ");
          Serial.println(ita);
          Serial.print("roh: ");
          Serial.println(roh);
          Serial.println(); // Print a blank line for readability
        } 

        JsonObject country = array[0].as<JsonObject>();

        JsonObject languages2 = country["languages"];

          Serial.print("Languages 2: \n");

          for (JsonPair kv : languages2) {
  
            Serial.print("Language Code: ");
            Serial.println(kv.key().c_str());  // Prints the language code (e.g., "deu")
            Serial.print("Language: ");
            Serial.println(kv.value().as<const char*>());
            Serial.println();
          } 

      } else {
        Serial.println("The JSON is not an array.");
      }

      /* 
      ***               EXPLICAÇÃO DO CÓDIGO  ****
      O objeto "nativeName" nos dados JSON tem um único par chave-valor, 
      onde a chave é "deu" (para o alemão). No código, o loop for (JsonPair kv : nativeNames) 
      itera sobre cada par chave-valor no objeto "nativeName".
      Como há apenas um par chave-valor (com a chave "deu"), 
      o loop será executado apenas uma vez.
      Dentro do loop, o código cria um JsonObject chamado nameObject e atribui a ele
      o valor associado à chave atual ("deu").
      Se houvesse chaves adicionais no objeto "nativeName", 
      como "en" para o inglês, o loop iteraria duas vezes - uma vez para a chave "deu" e 
      uma vez para a chave "en".
      Dentro do JsonObject associado à chave "deu" no objeto "nativeName", 
       existem outros dois pares chave-valor:
      
        * "official" - Que contém o nome oficial nativo em alemão, neste 
                       caso "Bundesrepublik Deutschland".
        * "common" - Que contém o nome comum nativo em alemão, neste caso "Deutschland".
      
        https://arduinojson.org/v6/api/jsonobject/begin_end/
      
      */
      
    } else {
      Serial.println("Erro na requisição HTTP");
    }
    http.end();
  } else {
    Serial.println("Erro ao conectar ao Wi-Fi");
  }
}

void loop() {
  // Não é necessário fazer nada aqui
}