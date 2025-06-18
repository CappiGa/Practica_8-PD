# **Práctica 8 - Buses de comunicación IV (UART) - Bucle de comunicación UART2**  

## **1. Descripción**  
Esta práctica implementa un **bucle de comunicación UART** en el ESP32-S3, donde los datos enviados desde el monitor serie (UART0) se redirigen a la **UART2** y viceversa. Se explora el funcionamiento básico de los protocolos asíncronos y la configuración de múltiples interfaces UART en el microcontrolador.  

---

## **2. Objetivos**  
- Configurar dos interfaces UART (**UART0 y UART2**) en el ESP32-S3.  
- Implementar un bucle de comunicación para redirigir datos entre UARTs.  
- Analizar el flujo de datos mediante el monitor serie.  

## **3- Resumen teórico**  
### **Protocolo UART**  
- **Comunicación asíncrona**: Sin señal de reloj, usa líneas independientes para TX (transmisión) y RX (recepción).  
- **Configuración típica**:  
  - Baud rate (ej. 115200 bps).  
  - 8 bits de datos, sin paridad, 1 bit de parada (`8N1`).  
- **Niveles lógicos**: 3.3V TTL en ESP32.  

### **UART en ESP32-S3**  
- **Interfaces UART**:  
  - **UART0**: Usada para comunicación con el PC (monitor serie).  
  - **UART1/UART2**: Asignables a pines GPIO.  
- **Pines por defecto para UART2**:  
  - **TXD2**: GPIO17  
  - **RXD2**: GPIO16  

---

## **4. Materiales**  
- **ESP32-S3**  
- **Cable USB-C** (para monitor serie).  
- **Cables dupont** (para loopback entre TXD2 y RXD2).  
![Image](https://github.com/user-attachments/assets/52be142e-d402-45c9-a72e-31bf7f7df0a9)
---

## **5. Desarrollo**  

### **5.1 Configuración del entorno**  
1. Crear un nuevo proyecto en PlatformIO. 


2. Configurar el archivo `platformio.ini`con el siguiente contenido:  
   ```ini
   [env:esp32-s3-devkitc-1]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   monitor_speed = 115200
   ```  

### **5.2 Programación**  
Código en `main.cpp`:  
```cpp
#include <Arduino.h>

#define RXD2 16  // GPIO16 para RX de UART2
#define TXD2 17  // GPIO17 para TX de UART2

void setup() {
  // Inicia UART0 (monitor serie)
  Serial.begin(115200);

  // Inicia UART2 en pines personalizados
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Bucle UART0 ↔ UART2 iniciado");
}

void loop() {
  // Redirige datos de UART0 (PC) a UART2
  if (Serial.available()) {
    char data = Serial.read();
    Serial2.write(data);
    Serial.print("Enviado a UART2: ");
    Serial.println(data);
  }

  // Redirige datos de UART2 a UART0 (PC)
  if (Serial2.available()) {
    char data = Serial2.read();
    Serial.print("Recibido de UART2: ");
    Serial.println(data);
  }
}
```  

**Explicación del código**:  
- **`Serial`**: Objeto para UART0 (comunicación con el PC).  
- **`Serial2`**: Objeto para UART2 (pines GPIO16/17).  
- **Flujo de datos**:  
  1. Los caracteres ingresados en el monitor serie se envían a UART2.  
  2. Si UART2 recibe datos (ej. loopback físico), se imprimen en el monitor.  

### **5.3 Conexión física**  
1. **Loopback**: Conectar **GPIO17 (TXD2) → GPIO16 (RXD2)** con un cable dupont.  
2. **Monitor serie**: Abrir en PlatformIO (115200 baudios).  

---

## **6. Resultados**  
- **Salida del monitor serie** (ejemplo):  
  ```plaintext
  Bucle UART0 ↔ UART2 iniciado
  Enviado a UART2: A
  Recibido de UART2: A
  ```  
- **Funcionamiento**:  
  - Cada carácter enviado al monitor serie se redirige a UART2 y vuelve a UART0 (loopback).  
  - Sin conexión loopback, solo se verán los mensajes de "Enviado".  
![Image](https://github.com/user-attachments/assets/a643477b-41b8-4a02-bb42-b1c0c28e2696)
![Image](https://github.com/user-attachments/assets/2143cabf-d5bd-4094-9607-143614ea325e)
---
