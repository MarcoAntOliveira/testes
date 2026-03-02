#include <Arduino.h>

// Pinos de controle (ajuste conforme seu circuito)
int ENA1 = 32;   // PWM Motor 1
int ENA2 = 4;   // PWM Motor 2
int IN1 = 27;
int IN2 = 14;
int IN3 = 33;
int IN4 = 12;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Configura PWM para ambos os motores
  ledcAttachPin(ENA1, 0);  // Canal 0
  ledcSetup(0, 5000, 8);   // 5 kHz, resolução de 8 bits

  ledcAttachPin(ENA2, 1);  // Canal 1
  ledcSetup(1, 5000, 8);   // 5 kHz, resolução de 8 bits

  // Pinos de direção
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Sentido 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Acelera progressivamente
  for (int speed = 0; speed <= 255; speed++) {
    ledcWrite(0, speed);  // Motor 1
    ledcWrite(1, speed);  // Motor 2
    delay(10);
  }

  // Para
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  delay(1000);

  // Sentido 2
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for (int speed = 0; speed <= 255; speed++) {
    ledcWrite(0, speed);
    ledcWrite(1, speed);
    delay(10);
  }

  ledcWrite(0, 0);
  ledcWrite(1, 0);
  delay(1000);
}
