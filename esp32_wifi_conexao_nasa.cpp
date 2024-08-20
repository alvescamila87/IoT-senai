#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "A";
const char* password = "12345678";
const char* apiKey = "thpFHlfM1koVrd5lXdaOIiUlhY18OXHLgOPJsf0Y";
const char* serverName = "https://api.nasa.gov/planetary/apod?api_key=";

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
    String url = String(serverName) + apiKey;
    http.begin(url.c_str());
    int httpResponseCode = http.GET();

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      
      // Parseia o JSON
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);

      const char* title = doc["title"];
      const char* date = doc["date"];
      const char* imageUrl = doc["url"];
      const char* explanation = doc["explanation"];
     

      Serial.println("Título: " + String(title));
      Serial.println("Explicação: " + String(explanation));     
      Serial.println("Data: " + String(date));
      Serial.println("URL da Imagem: " + String(imageUrl));
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
