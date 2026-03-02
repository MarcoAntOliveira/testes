#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  if (!SerialBT.begin("ESP32_TESTE")) {
    Serial.println("❌ Falha ao iniciar Bluetooth — este chip pode não ter BT clássico!");
  } else {
    Serial.println("✅ Bluetooth clássico iniciado com sucesso!");
    Serial.println("Agora procure por 'ESP32_TESTE' no Bluetooth do seu PC ou celular.");
  }
}

void loop() {
    if (!SerialBT.begin("ESP32_TESTE")) {
     Serial.println("❌ Falha ao iniciar Bluetooth — este chip pode não ter BT clássico!");
    } else {
     Serial.println("✅ Bluetooth clássico iniciado com sucesso!");
     Serial.println("Agora procure por 'ESP32_TESTE' no Bluetooth do seu PC ou celular.");
    }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
}
