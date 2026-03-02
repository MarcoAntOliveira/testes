#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

// Pinos de controle
//int ENA = 25;   // PWM
int IN1 = 27;
int IN2 = 14;

const char* ap_ssid = "ESP32_Rede";
const char* ap_pass = "12345678";
const uint16_t PORT = 3333;

WiFiServer server(PORT);
int sentido = 1; // variável global

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Configuração PWM
  ledcSetup(0, 5000, 8);   // Canal 0, 5 kHz, 8 bits
  //ledcAttachPin(ENA, 0);

  // Cria rede Wi-Fi
  WiFi.softAP(ap_ssid, ap_pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP: "); Serial.println(IP);

  server.begin();
  Serial.printf("Servidor TCP rodando na porta %u\n", PORT);
}

String readLine(WiFiClient &client) {
  String line = "";
  unsigned long start = millis();
  while (millis() - start < 2000) { // timeout 2s
    while (client.available()) {
      char c = client.read();
      if (c == '\r') continue;
      if (c == '\n') return line;
      line += c;
      start = millis();
    }
    delay(1);
  }
  return line;
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      if (client.available()) {
        String msg = readLine(client);
        if (msg.length() == 0) continue;

        Serial.print("Recebido: ");
        Serial.println(msg);

        // Alterna o sentido do motor
        if (sentido == 1)
          sentido = 2;
        else
          sentido = 1;

        client.println("OK");

        // Executa o movimento conforme o sentido
        if (sentido == 1) {
          Serial.println("Motor no sentido 1");
           for (int speed = 255; speed >= 0; speed--) {
              ledcWrite(0, speed);
              delay(100);
            }
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
        } else {
          Serial.println("Motor no sentido 2");
            for (int speed = 255; speed >=0; speed--) {
              ledcWrite(0, speed);
              delay(100);
            }
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
        }

        // Aceleração progressiva
        for (int speed = 0; speed <= 255; speed++) {
          ledcWrite(0, speed);
          delay(10);
        }

        // Para o motor
        ledcWrite(0, 0);
        delay(1000);
      }
      delay(1);
    }

    client.stop();
    Serial.println("Cliente desconectado");
  }
}
