/*
 * Arquivo: CatImageFetcher.ino
 * Autor: Giovanni Rozza
 * Data: 26 de agosto de 2024
 * 
 * Descrição:
 * Este código conecta um dispositivo ESP32 a uma rede Wi-Fi e faz uma requisição HTTP 
 * à API "The Cat API" para obter uma lista de imagens de gatos. Os dados retornados 
 * em formato JSON são analisados usando a biblioteca ArduinoJson, e as informações sobre 
 * as imagens, como ID, URL, largura e altura, são extraídas e exibidas no monitor serial.
 * 
 * Bibliotecas Utilizadas:
 * - WiFi.h: para conectar o ESP32 à rede Wi-Fi.
 * - HTTPClient.h: para enviar a requisição HTTP e receber a resposta.
 * - ArduinoJson.h: para parsear e manipular o JSON recebido.
 * 
 * Funcionalidade:
 * 1. Conectar à rede Wi-Fi especificada.
 * 2. Realizar uma requisição HTTP GET à API "The Cat API".
 * 3. Parsear a resposta JSON e extrair informações das imagens.
 * 4. Exibir as informações no monitor serial.
 * 
 * Notas:
 * - Este código foi desenvolvido para ser executado em um ESP32.
 * - A API "The Cat API" retorna informações sobre imagens de gatos em formato JSON.
 * - A função loop() não é utilizada neste exemplo.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "https://api.thecatapi.com/v1/images/search?limit=3";

void setup() {
  Serial.begin(115200);
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.println("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(WiFi.status());
  }
  Serial.println("Conectado ao WiFi");

  // Faz a requisição HTTP
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //String url = String(serverName) + apiKey;
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
      
        /*
       * O ArduinoJson não consegue converter diretamente de JsonVariantConst para um ponteiro de char* não constante. 
       * Isso acontece porque o ponteiro precisa apontar para uma área de memória que possa ser modificada, 
       * mas o JsonVariantConst é um objeto constante.
       * 
       * O método .as<T>() faz parte da biblioteca ArduinoJson e é utilizado para converter um valor armazenado em 
       * um objeto JSON para um tipo de dado específico em C++.

       Quando você trabalha com JSON no Arduino, os valores armazenados nos objetos JSON (JsonVariant, JsonObject, etc.) 
       podem ser de diferentes tipos: inteiros, strings, booleanos, floats, etc. O método .as<T>() é usado para extrair o
       valor do JSON e convertê-lo para o tipo de dado que você deseja trabalhar no seu código.
       */
       
      // Check if doc is an array
      if (doc.is<JsonArray>()) {
        

        JsonArray array = doc.as<JsonArray>();

        // Iterate through the array using index
        for (size_t i = 0; i < array.size(); i++) {
          JsonObject gatos = array[i].as<JsonObject>();
          String idImagem = gatos["id"].as<String>();
          String urlImagem = gatos["url"].as<String>();
      
          // Retrieve integer attributes
          int width = gatos["width"].as<int>();
          int height = gatos["height"].as<int>(); 

          // Print the extracted values
          Serial.println("*** GATO #" + String(i) + " ***");
          Serial.print("Id da imagem : ");
          Serial.println(idImagem);
          Serial.print("Url imagem : ");
          Serial.println(urlImagem);
          Serial.print("Width: ");
          Serial.println(width);
          Serial.print("Height: ");
          Serial.println(height);
   
          Serial.println(); // Print a blank line for readability
        }
      } else {
        Serial.println("The JSON is not an array.");
      }

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