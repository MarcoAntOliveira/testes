#include <Arduino.h>

#include <Servo.h>

Servo meuServo;

void setup() {
  meuServo.attach(9); // pino PWM
}

void loop() {
  meuServo.write(0);   // posição 0°
  delay(1000);
  meuServo.write(90);  // posição 90°
  delay(1000);
  meuServo.write(180); // posição 180°
  delay(1000);
}
