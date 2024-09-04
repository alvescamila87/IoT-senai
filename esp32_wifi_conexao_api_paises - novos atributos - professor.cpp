#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "https://restcountries.com/v3.1/name/swiss";

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
        for (size_t i = 0; i < array.size(); i++) // laço FOR NEXT PRINCIPAL
        {
          // OBJETO PAIS, CONTEM TODOS OS ATRIBUTOS
          JsonObject country = array[i].as<JsonObject>();

          // Extract "common" and "official" names
          const char* commonName = country["name"]["common"];
          const char* officialName = country["name"]["official"];

          // Print the extracted values
          Serial.print("Common Name: ");
          Serial.println(commonName);
          Serial.print("Official Name: ");
          Serial.println(officialName);
          Serial.println(); // Print a blank line for readability

          JsonObject nativeNames = country["name"]["nativeName"];
    
          // Iterate over each language entry in nativeName
          for (JsonPair kv : nativeNames) {
            JsonObject nameObject = kv.value().as<JsonObject>();
            const char* officialNative = nameObject["official"];
            const char* commonNative = nameObject["common"];
    
            Serial.print("Language Code: ");
            Serial.println(kv.key().c_str());  // Prints the language code (e.g., "deu")
            Serial.print("Official Native Name: ");
            Serial.println(officialNative);
            Serial.print("Common Native Name: ");
            Serial.println(commonNative);
            Serial.println();
          }
          // EXERCICIO
          // Extrai "altSpellings" array
          JsonArray altSpellings = country["altSpellings"].as<JsonArray>();
          Serial.println("Alternate Spellings:");
          for (size_t j = 0; j < altSpellings.size(); j++) {
            Serial.print("- ");
            Serial.println(altSpellings[j].as<const char*>());
          }
          Serial.println();

          //EXERCICIO
          // Extrai "region" and "subregion"
          const char* region = country["region"];
          const char* subregion = country["subregion"];
          Serial.print("Region: ");
          Serial.println(region);
          Serial.print("Subregion: ");
          Serial.println(subregion);
          Serial.println();

          //EXERCICIO
          // Extrai "languages" object
          JsonObject languages = country["languages"];
          Serial.println("Languages:");
          for (JsonPair kv : languages) {
            Serial.print("- ");
            Serial.print(kv.key().c_str());  // Language code (e.g., "fra")
            Serial.print(": ");
            Serial.println(kv.value().as<const char*>());  // Language name (e.g., "French")
          }
          Serial.println();
          
        } // laço FOR NEXT PRINCIPAL
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