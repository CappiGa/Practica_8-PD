#include <Arduino.h>

#define RXD2 16  // Pin RX de UART2
#define TXD2 17  // Pin TX de UART2

void setup() {
  // Inicia comunicación serie con el PC
  Serial.begin(115200);

  // Inicia UART2 en los pines especificados
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.println("ESP32 UART2 Loop test");
}

void loop() {
  // Si hay datos desde el monitor serie, los envía por UART2
  if (Serial.available()) {
    char incoming = Serial.read();
    Serial2.write(incoming);
    Serial.print("UART0 -> UART2: ");
    Serial.println(incoming);
  }

  // Si hay datos devueltos desde UART2 (loopback), los imprime en el monitor
  if (Serial2.available()) {
    char incoming = Serial2.read();
    Serial.print("UART2 -> UART0: ");
    Serial.println(incoming);
  }
}