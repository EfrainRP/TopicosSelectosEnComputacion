#include <Wire.h>;
int LED = 2;
int x = 0;

void setup() {
  // Define el pin LED como salida
  pinMode(LED, OUTPUT);
  Wire.begin(9);                 // Arrancar el bus I2C como esclavo en la dirección 9
  Wire.onReceive(receiveEvent);  // Conecta una función para disparar cuando se recibe algo.
}

void receiveEvent(int bytes) {
  x = Wire.read();  // leer un carácter del I2C
}

void loop() {
  // Si el valor recibido es 0, el LED parpadea durante 200 ms.
  if (x == 0) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  // Si el valor recibido es 3, el LED parpadea durante 400 ms.
  if (x == 3) {
    digitalWrite(LED, HIGH);
    delay(400);
    digitalWrite(LED, LOW);
    delay(400);
  }
}