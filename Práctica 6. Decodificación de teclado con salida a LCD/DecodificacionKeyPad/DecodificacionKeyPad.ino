#include <LiquidCrystal.h>;
#include <Keypad.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] =
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {15, 14, 2, 3};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(void) {
  lcd.begin (16,2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Keypad: ");
}

void loop(void) {
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    Serial.println(key);

    lcd.setCursor(0,7);
    lcd.print(key);
    delay(1000);
  }
}
