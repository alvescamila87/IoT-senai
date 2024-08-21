#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "A";
const char* password = "12345678";
//const char* apiKey = "thpFHlfM1koVrd5lXdaOIiUlhY18OXHLgOPJsf0Y";
const char* serverName = "https://api.thecatapi.com/v1/images/search?limit=1";

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
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      
      // Parseia o JSON
      DynamicJsonDocument doc(5000);
      deserializeJson(doc, payload);

      JsonObject gatos = doc[0];

      char* id = gatos["id"];
      char* url = gatos["url"];
      int   width = gatos["width"];
      int   height = gatos["height"];

      Serial.println("ID: " + String(id));
      Serial.println("URL da imagem: " + String(url));     
      Serial.println("Largura da imagem: " + String(width));
      Serial.println("Altura da imagem: " + String(height));

      JsonObject gatos = doc[1];

      char* id = gatos["id"];
      char* url = gatos["url"];
      int   width = gatos["width"];
      int   height = gatos["height"];
      
      Serial.println("ID: " + String(id));
      Serial.println("URL da imagem: " + String(url));     
      Serial.println("Largura da imagem: " + String(width));
      Serial.println("Altura da imagem: " + String(height));

      JsonObject gatos = doc[2];

      char* id = gatos["id"];
      char* url = gatos["url"];
      int   width = gatos["width"];
      int   height = gatos["height"];    

      Serial.println("ID: " + String(id));
      Serial.println("URL da imagem: " + String(url));     
      Serial.println("Largura da imagem: " + String(width));
      Serial.println("Altura da imagem: " + String(height));

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
