#include <Arduino.h>

// Segundo motor
int ENA2 = 4;  // PWM
int IN3 = 33;
int IN4 = 12  ;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Configuração PWM
  ledcSetup(1, 5000, 8);    // Canal 1, 5 kHz, 8 bits
  ledcAttachPin(ENA2, 1);   // ENA2 -> canal 1 PWM

  // Direção
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Teste do segundo motor iniciado!");
}

void loop() {
  // --- Sentido 1 ---
  Serial.println("Sentido 1");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int speed = 0; speed <= 255; speed++) {
    ledcWrite(1, speed);
    delay(10);
  }

  ledcWrite(1, 0);
  delay(1000);

  // --- Sentido 2 ---
  Serial.println("Sentido 2");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for (int speed = 0; speed <= 255; speed++) {
    ledcWrite(1, speed);
    delay(10);
  }

  ledcWrite(1, 0);
  delay(1000);
}
