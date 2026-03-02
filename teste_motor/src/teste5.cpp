#include <Arduino.h>

// === Configuração dos pinos ===
const int ENA = 32;   // PWM do motor (Enable)
const int IN1 = 27;   // Direção 1
const int IN2 = 14;   // Direção 2

// Canal e configuração do PWM
const int PWM_CANAL = 0;
const int PWM_FREQUENCIA = 5000; // 5 kHz
const int PWM_RESOLUCAO = 8;     // 8 bits (0-255)

void setup() {
  Serial.begin(115200);
  Serial.println("Teste de motor iniciado");

  // Configura PWM
  ledcSetup(PWM_CANAL, PWM_FREQUENCIA, PWM_RESOLUCAO);
  ledcAttachPin(ENA, PWM_CANAL);

  // Configura pinos de direção
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Garante estado inicial
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM_CANAL, 0);
}

void loop() {
  Serial.println("Gira para um lado...");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM_CANAL, 200); // velocidade média
  delay(2000);

  Serial.println("Parando...");
  ledcWrite(PWM_CANAL, 0);
  delay(1000);

  Serial.println("Gira para o outro lado...");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(PWM_CANAL, 200);
  delay(2000);

  Serial.println("Parando...");
  ledcWrite(PWM_CANAL, 0);
  delay(2000);
}
