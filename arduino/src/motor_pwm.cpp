#include <Arduino.h>

// Teste TB6612FNG com ESP8266 (NodeMCU)

#define PWMA 14   // D5 - controle de velocidade (PWM)
#define AIN1 12   // D6 - direção
#define AIN2 13   // D7 - direção
#define STBY 15   // D8 - standby

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  Serial.begin(115200);
  Serial.println("Teste TB6612FNG iniciado");

  digitalWrite(STBY, HIGH); // habilita o driver
}

void loop() {
  // Gira para um lado
  Serial.println("Gira para frente");
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 600);  // velocidade (0–1023 no ESP8266)
  delay(2000);

  // Para
  Serial.println("Parando");
  analogWrite(PWMA, 0);
  delay(1000);

  // Gira para o outro lado
  Serial.println("Gira para trás");
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 600);
  delay(2000);

  // Para novamente
  Serial.println("Parando");
  analogWrite(PWMA, 0);
  delay(1000);
}