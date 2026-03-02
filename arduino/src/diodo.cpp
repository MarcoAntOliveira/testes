#include <Arduino.h>

// Teste simples de diodo usando Arduino
// Liga o anodo no pino 8 e o catodo no pino 9
// Vai acender o LED embutido se o diodo conduzir

int anodo = 8;
int catodo = 9;

void setup() {
  pinMode(anodo, OUTPUT);
  pinMode(catodo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(anodo, HIGH); // aplica tensão no anodo
  delay(10);

  int leitura = digitalRead(catodo);
  if (leitura == HIGH) {
    Serial.println("Diodo conduz (OK)");
  } else {
    Serial.println("Diodo não conduz");
  }

  digitalWrite(anodo, LOW);
  delay(1000);
}