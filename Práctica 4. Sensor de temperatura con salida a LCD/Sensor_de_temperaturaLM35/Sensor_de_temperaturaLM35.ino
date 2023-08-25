#include "rgb_lcd.h"
rgb_lcd lcd;

float Temperatura;

void setup() {
  lcd.begin(16, 2);
  lcd.print("ARDUINO"); // Print a message to the LCD.
  delay(1000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);  //cursor en la posición 0 de la lcd
  lcd.print("Temperatura");

  Temperatura= (500.0*analogRead(4)/1024.0);//Formula para el calculo de la temperatura con LM35
  lcd.setCursor(0, 1); 
  lcd.print(Temperatura);
  lcd.setCursor(5, 1); 
  lcd.print(" C");
  
  delay (3000);
}