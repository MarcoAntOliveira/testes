/*
  Teste de comunicação com o módulo RFID MFRC522
  - Verifica se o módulo responde via SPI
  - Mostra a versão do chip no Serial Monitor

  Ligações padrão (Arduino UNO):
    SDA(SS) -> D10
    SCK     -> D13
    MOSI    -> D11
    MISO    -> D12
    RST     -> D9
    3.3V    -> 3.3V (⚠️ não use 5V)
    GND     -> GND
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Iniciando teste do módulo RFID MFRC522..."));

  SPI.begin();
  rfid.PCD_Init();

  delay(100);
  Serial.println(F("Verificando comunicação com o RFID..."));

  byte version = rfid.PCD_ReadRegister(MFRC522::VersionReg);
  if (version == 0x00 || version == 0xFF) {
    Serial.println(F("❌ ERRO: RFID não detectado!"));
    Serial.println(F("Verifique a fiação e se o módulo está alimentado com 3.3V."));
  } else {
    Serial.print(F("✅ Módulo detectado. Versão do chip: 0x"));
    Serial.println(version, HEX);
    Serial.println(F("RFID funcionando corretamente!"));
  }
}

void loop() {
  // Nada a fazer - apenas mantém o programa rodando
}
