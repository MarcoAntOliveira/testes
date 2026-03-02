#include <Bluepad32.h>

GamepadPtr myGamepad;

void onConnectedGamepad(GamepadPtr gp) {
    Serial.println("Controle conectado!");
    myGamepad = gp;
}

void onDisconnectedGamepad(GamepadPtr gp) {
    Serial.println("Controle desconectado!");
    myGamepad = nullptr;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando Bluepad32...");

    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
    BP32.forgetBluetoothKeys();  // limpa conexões anteriores
}

void loop() {
    BP32.update();

    if (myGamepad && myGamepad->isConnected()) {
        if (myGamepad->a()) Serial.println("Botão A pressionado!");
        if (myGamepad->b()) Serial.println("Botão B pressionado!");
    }

    delay(50);
}
