#include <LiquidCrystal.h>;

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

//  Variables
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int PulseWire = 0;  // PulseSensor se conectara al PIN ANALOGICO 0
int Threshold = 550;      // Determina qué señal "contar como un latido" y cuál ignorar.

PulseSensorPlayground pulseSensor;  // Crea una instancia del objeto PulseSensorPlayground llamada "pulseSensor"

void setup() {
  lcd.begin(16, 2); //Iniciazlizacion de la pantalla LCD

  Serial.begin(9600);  // For Serial Monitor

  // Configura el objeto PulseSensor, asignándole nuestras variables.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  // Vuelve a verificar que se haya creado el objeto "pulseSensor" y que comenzó a ver una señal.
  if (pulseSensor.begin()) {
    Serial.println("Sensor de pulso Iniciado");
    lcd.setCursor(0, 0);
    lcd.print("Sensor de pulso Iniciado");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BPM: ");
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();  // pulseSensor devuelve BPM como un "int".
  if (pulseSensor.sawStartOfBeat()) {           // Prueba constantemente para ver si "sucedió un latido"
    Serial.print("BPM: ");                      // Se imprime "BPM: "
    Serial.println(myBPM);                      // Se imprime el valor de myBPM.
    lcd.setCursor(5,0);                         // Se coloca en la posicion x=5,y=0 del LCD
    lcd.print(myBPM);                           // Se imprime el valor myBPM en el LCD respectivamente del cursosr 
  }
  delay(10);
}
