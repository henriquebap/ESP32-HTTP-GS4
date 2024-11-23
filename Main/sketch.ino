#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

// Credenciais Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configuração do servidor de teste
// const char* testServer = "https://httpbin.org/post";
const char* serverName = "https://backend.thinger.io/v3/users/henriquebap/devices/Esp32Gs/callback/data";
const char* token = "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEZXZpY2VDYWxsYmFja19Fc3AzMkdzIiwic3ZyIjoidXMtZWFzdC5hd3MudGhpbmdlci5pbyIsInVzciI6ImhlbnJpcXVlYmFwIn0.1DQskKw5oH0rawoqE05E8Zf76jz7OfR1Uh9Sq8JhP2M";


// Configurações do DHT22
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configurações do LDR
#define LDR_PIN 36

void connectWiFi() {
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LDR_PIN, INPUT);

  // Conexão Wi-Fi
  connectWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Leitura dos sensores
    float temperature = dht.readTemperature();
    int ldrValue = analogRead(LDR_PIN);

    if (isnan(temperature)) {
      Serial.println("Erro ao ler o sensor DHT22!");
      return;
    }

    // Criação do JSON
    StaticJsonDocument<256> jsonDoc;
    jsonDoc["temperature"] = temperature;
    jsonDoc["ldr_value"] = ldrValue;

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    // Envio dos dados via HTTP POST para o servidor de teste
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json;charset=UTF-8");
    http.addHeader("Authorization", token);

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Código de resposta: ");
      Serial.println(httpResponseCode);
      Serial.print("Payload enviado: ");
      Serial.println(jsonData);
      Serial.print("Resposta do servidor: ");
      Serial.println(response);
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi desconectado! Tentando reconectar...");
    connectWiFi();
  }
  delay(5000); // Intervalo de 5 segundos entre as leituras
}
