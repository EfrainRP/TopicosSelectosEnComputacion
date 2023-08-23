#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ARDUINO");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0, 0);  //cursor en la posición 0 de la lcd
  lcd.print("Probador pilas");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(0) * 5.00 / 1024);  //conversión de binario a voltaje
  lcd.print("V=>");
  lcd.setCursor(8, 1);
  if ((analogRead(0) * 5.00 / 1023.00) > 1.40) {
    lcd.print("Perfecto");
  } else if ((analogRead(0) * 5.00 / 1023.00) > 1.20 && (analogRead(0) * 5.00 / 1023.00) < 1.40) {
    lcd.print("Bueno");
  } else if ((analogRead(0) * 5.00 / 1023.00) < 1.20 && (analogRead(0) * 5.00 / 1023.00) > 0.30) {
    lcd.print("Regular");
  } else if ((analogRead(0) * 5.00 / 1023.00) < 0.3) {
    lcd.print("Malo");
  } else {
    lcd.print(" ");
  }
  delay(250);
}
