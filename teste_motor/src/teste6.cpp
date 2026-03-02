
#include<Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA=21, SCL=22
  delay(100);
  Serial.println("\nI2C Scanner iniciado. Procurando dispositivos...");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado no endereco 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    } else if (error==4) {
      Serial.print("Erro desconhecido no endereco 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("Nenhum dispositivo encontrado\n");
  else
    Serial.println("Busca finalizada\n");

  delay(5000); // repete a cada 5s
}

