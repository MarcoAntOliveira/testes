#include <Arduino.h>
#include <WiFi.h>

// --- PINOS ---
#define ENA1 32
#define ENA2 4
#define IN1 27
#define IN2 14
#define IN3 33
#define IN4 12

// --- WIFI AP ---
const char* ssid = "CARRO_ESP32";
const char* password = "12345678";

WiFiServer server(3333);

// Variável global que guarda comando
volatile char comando = 'P'; // P = parado

// ---------------- TASK DO MOTOR ----------------
void motorTask(void *param){
  while(true){
    if(comando == 'F'){   // Frente
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      ledcWrite(0, 200);
      ledcWrite(1, 200);
    }
    else if(comando == 'T'){  // Trás
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      ledcWrite(0, 200);
      ledcWrite(1, 200);
    }
    else {   // Parado
      ledcWrite(0, 0);
      ledcWrite(1, 0);
    }

    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

// ---------------- TASK DO SERVIDOR TCP ----------------
void tcpTask(void *param){
  server.begin();
  Serial.println("Servidor TCP iniciado na porta 3333");

  while(true){
    WiFiClient client = server.available();
    if(client){
      Serial.println("Cliente conectado");

      while(client.connected()){
        if(client.available()){
          char c = client.read();
          Serial.printf("Recebido: %c\n", c);

          if(c == 'F' || c == 'T' || c == 'P'){
            comando = c;
          }
        }
      }

      client.stop();
      Serial.println("Cliente desconectado");
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void setup(){
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM
  ledcAttachPin(ENA1, 0);
  ledcSetup(0, 5000, 8);

  ledcAttachPin(ENA2, 1);
  ledcSetup(1, 5000, 8);

  // Modo AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());

  // Criar tasks
  xTaskCreatePinnedToCore(motorTask, "MOTOR", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(tcpTask, "TCP", 4096, NULL, 1, NULL, 0);
}

void loop(){
  // NÃO USA LOOP NO FREERTOS
}
