#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA=21, SCL=22 (ajuste se usar outros pinos)

  Serial.println("Iniciando QMC5883L...");

  compass.init();

  // Calibração inicial opcional
  compass.setCalibration(-500, 500, -500, 500, -500, 500);

  Serial.println("Sensor pronto!");
  delay(1000);
}

void loop() {
  compass.read();

  int x = compass.getX();
  int y = compass.getY();
  int z = compass.getZ();
  int azimuth = compass.getAzimuth();

  Serial.println("---- Leitura de Sensor ----");
  Serial.printf("Mag X: %d | Y: %d | Z: %d\n", x, y, z);
  Serial.printf("Direção (Azimute): %d°\n", azimuth);
  Serial.println("-----------------------------\n");

  delay(1000);
}
