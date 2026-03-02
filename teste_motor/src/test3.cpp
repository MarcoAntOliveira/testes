#include <Arduino.h>

// ===============================
// Pinos de controle (ajuste conforme seu circuito)
int ENA1 = 32;   // PWM Motor 1
int ENA2 = 4;    // PWM Motor 2
int IN1 = 27;
int IN2 = 14;
int IN3 = 33;
int IN4 = 12;
// ===============================

// Canais PWM (ESP32 tem até 16)
#define PWM_CH1 0
#define PWM_CH2 1

// Frequência e resolução PWM
#define PWM_FREQ 1000  // 1 kHz
#define PWM_RES 8      // 8 bits (0-255)

// ===============================
// Funções auxiliares
void motor1(int velocidade, bool sentidoHorario);
void motor2(int velocidade, bool sentidoHorario);
// ===============================

void setup() {
  Serial.begin(115200);

  // Configura pinos de direção
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configura PWM para cada motor
  ledcSetup(PWM_CH1, PWM_FREQ, PWM_RES);
  ledcAttachPin(ENA1, PWM_CH1);

  ledcSetup(PWM_CH2, PWM_FREQ, PWM_RES);
  ledcAttachPin(ENA2, PWM_CH2);

  Serial.println("=== Teste de dois motores com PWM iniciado ===");
}

void loop() {
  int velocidade = 200; // valor de 0 a 255

  // Motor 1 horário, Motor 2 anti-horário
  motor1(velocidade, true);
  motor2(velocidade, false);
  Serial.println("Motor 1 horário | Motor 2 anti-horário");
  delay(2000);

  // Inverte os sentidos
  motor1(velocidade, false);
  motor2(velocidade, true);
  Serial.println("Motor 1 anti-horário | Motor 2 horário");
  delay(2000);

  // Para motores
  motor1(0, true);
  motor2(0, true);
  Serial.println("Motores parados");
  delay(2000);
}

// ===============================
// Implementação das funções
void motor1(int velocidade, bool sentidoHorario) {
  if (sentidoHorario) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  ledcWrite(PWM_CH1, velocidade);
}

void motor2(int velocidade, bool sentidoHorario) {
  if (sentidoHorario) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  ledcWrite(PWM_CH2, velocidade);
}
