// ESP32_AP_TCP_Server.ino
#include <WiFi.h>

const char* ssid = "ESP32_AP_Marcos";   // nome da rede do ESP32 (mude se quiser)
const char* password = "12345678";     // senha do AP (min 8 chars)

WiFiServer server(3333); // Porta do servidor TCP

void setup() {
  Serial.begin(115200);
  delay(500);

  // Inicia modo AP
  Serial.printf("Criando AP: %s\n", ssid);
  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP(); // normalmente 192.168.4.1
  Serial.print("AP IP address: ");
  Serial.println(ip);

  server.begin();
  Serial.println("Servidor TCP iniciado, aguardando clientes...");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Cliente conectado!");
    // Enquanto o cliente estiver conectado
    while (client.connected()) {
      // Exemplo de dados: tempo desde boot em ms
      unsigned long tempo = millis();
      String mensagem = String("Tempo (ms): ") + tempo + "\n";

      // Envia para o cliente
      client.print(mensagem);
      Serial.print("Enviado: ");
      Serial.print(mensagem);

      // Se o cliente enviar algo, podemos ler (opcional)
      if (client.available()) {
        String recebido = client.readStringUntil('\n');
        recebido.trim();
        if (recebido.length() > 0) {
          Serial.print("Cliente disse: ");
          Serial.println(recebido);
        }
      }

      delay(2000); // intervalo de envio (2s)
    }

    Serial.println("Cliente desconectado.");
    client.stop();
  }

  // pequena pausa para não travar o loop
  delay(10);
}