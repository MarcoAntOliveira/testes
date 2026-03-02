#include <Arduino.h>
int base = 7;

void setup() {
  pinMode(base, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(base, HIGH); // polariza a base
  delay(100);
  Serial.println("Se LED acendeu: Transistor OK");
  
  digitalWrite(base, LOW);
  delay(1000);
}