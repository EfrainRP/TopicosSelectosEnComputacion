#include <Wire.h>;

int x = 0;

void setup() {
  Wire.begin();  // Arrancar el bus I2C como maestro
}

void loop() {
  Wire.beginTransmission(9);  // iniciando transmisión al dispositivo #9
  Wire.write(x);              // manda x
  Wire.endTransmission();     // dejar de transmitir
  x++;                        // Incrementa x
  if (x > 5) x = 0;           // ` resetea x; una vez que llegue a 6
  delay(500);
}
