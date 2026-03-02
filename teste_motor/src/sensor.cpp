#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BME280.h>
#include <MPU9250_asukiaaa.h>

// Instâncias dos sensores
Adafruit_BMP280 bmp; 
Adafruit_BME280 bme; 
MPU9250_asukiaaa mySensor;

// Variáveis de controle
bool isBMP = false;
bool isBME = false;
uint8_t bmpAddress = 0x76; // padrão inicial

void scanI2C() {
  Serial.println("🔍 Escaneando dispositivos I2C...");
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("➡️ Dispositivo encontrado no endereço 0x");
      Serial.println(i, HEX);
      delay(5);
    }
  }
  Serial.println("✅ Varredura I2C concluída.\n");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL do ESP32

  Serial.println("=== Inicializando GY-91 (MPU9250 + BMP/BME280) ===");
  scanI2C();

  // Testa o BMP280 e BME280 nos dois endereços possíveis
  if (bmp.begin(0x76)) {
    isBMP = true;
    bmpAddress = 0x76;
  } else if (bmp.begin(0x77)) {
    isBMP = true;
    bmpAddress = 0x77;
  } else if (bme.begin(0x76)) {
    isBME = true;
    bmpAddress = 0x76;
  } else if (bme.begin(0x77)) {
    isBME = true;
    bmpAddress = 0x77;
  }

  if (isBMP) {
    Serial.print("✅ Sensor BMP280 detectado no endereço 0x");
    Serial.println(bmpAddress, HEX);
  } else if (isBME) {
    Serial.print("✅ Sensor BME280 detectado no endereço 0x");
    Serial.println(bmpAddress, HEX);
  } else {
    Serial.println("❌ Nenhum BMP/BME280 detectado! Verifique fiação e endereço I2C.");
  }

  // Inicializa MPU9250
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  Serial.println("✅ MPU9250 inicializado.\n");
}

void loop() {
  // Atualiza leituras do MPU9250
  mySensor.accelUpdate();
  mySensor.gyroUpdate();
  mySensor.magUpdate();

  Serial.println("---- Leitura de Sensores ----");

  // Leitura da aceleração
  Serial.print("Aceleração X: "); Serial.print(mySensor.accelX());
  Serial.print(" | Y: "); Serial.print(mySensor.accelY());
  Serial.print(" | Z: "); Serial.println(mySensor.accelZ());

  // Leitura da temperatura e pressão
  if (isBMP) {
    Serial.print("Temperatura BMP280: ");
    Serial.print(bmp.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressão: ");
    Serial.print(bmp.readPressure() / 100.0);
    Serial.println(" hPa");
  } else if (isBME) {
    Serial.print("Temperatura BME280: ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressão: ");
    Serial.print(bme.readPressure() / 100.0);
    Serial.println(" hPa");

    Serial.print("Umidade: ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
  } else {
    Serial.println("⚠️ Nenhum sensor BMP/BME280 ativo!");
  }

  Serial.println("-----------------------------\n");
  delay(2000);
}
