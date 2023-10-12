#include <Servo.h>

Servo myservo;  // Crea una instancia para el control del servo

void setup() {
  myservo.attach(9);  // Configura el pin 9 para mandar la señal del servo
  myservo.write(0);   //El servo se movera a la posicion o grado 0
}

void loop() {
  for (int pos = 0; pos < 180; pos++) { // Ira de los 0 grados a los 180 grados en pasos de uno en uno
    myservo.write(pos);              // Le dira la posicion a ir al servomotor 
    delay(25);                       // Espera de 25 ms para que el servo se posicione
  }
  for (int pos = 180; pos > 0; pos--) { // Ira de los 180 grados a los 0 grados en pasos de uno en uno
    myservo.write(pos);              // Le dira la posicion a ir al servomotor
    delay(25);                       // Espera de 25 ms para que el servo se posicione
  }
}
