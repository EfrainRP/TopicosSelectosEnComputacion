#include <LiquidCrystal.h>;
#include <Keypad.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 4, 5, 6, 7 };
byte colPins[COLS] = { 15, 14, 2, 3 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char numIN[2];  //Arreglo para introducir numeros del teclado
int pos = 0;
bool ready1 = false, oper = false;
int op, oper1, oper2;

void cifras(char key) {   //Fucnion para obtener los valores del teclado a un numero, junto con el de la confirmacion
  switch (key) {
    case '0' ... '9':
      numIN[pos++] = key;
      if (pos >= 2) {
        pos = 0;
      }
      if (numIN[1]) { //Determina como juntara el arreglo para determinar el numero correcto
        op = (String(numIN[0]).toInt() * 10) + String(numIN[1]).toInt();
        numIN[1] = 0;
      } else {
        op = String(numIN[0]).toInt();
      }
      break;
    case '#': //Tecla de confimacion con el #
      if (!ready1) {  //Cuando estemos introduciendo la primera cifra
        oper1 = op;   //Guardara la primera cifra y se reiniciara sus valores para la sig. cifra
        limpiar();
        ready1 = true;
        pos = 0;

      } else {  //Cuando estemos introduciendo la segunda cifra
        oper2 = op; //Guardara la primera cifra y se reiniciara sus valores para el sig. estado
        limpiar();
        ready1 = false;
        //Serial.println(oper1);
        //Serial.println(oper2);
        if (oper1 >= oper2) { //El valor del operando1 debe ser mayor o igual que el operando2
          oper = true;
        }
        Serial.println(oper);
      }
      break;
  }
}
void limpiar() {//Funcion para limpiar nuestos valores basicas
  numIN[0] = 0;
  numIN[1] = 0;
  op = 0;  //Limpiar resultado para LCD
  lcd.clear();
  pos = 0;
}
void setup() {
  lcd.begin(16, 2);  //Inicializando LCD
  lcd.clear();       //Limpiamos la LCD
  Serial.begin(9600); 
}

void loop() {
  char key = keypad.getKey(); //Variable que guarda el valor de teclado

  while (!ready1) { //Ciclo para introducir la primera cifra
    key = keypad.getKey();
    lcd.setCursor(0, 0);
    lcd.print("Primer Operando: ");
    cifras(key);
    if (op) {
      lcd.setCursor(0, 1);
      lcd.print(op);
      lcd.print("  ");
    }
  }
  while (ready1) {  //Ciclo para introducir la segunda cifra
    key = keypad.getKey();
    lcd.setCursor(0, 0);
    lcd.print("Segundo Operando: ");
    cifras(key);
    if (op) {
      lcd.setCursor(0, 1);
      lcd.print(op);
      lcd.print("  ");
    }
  }

  lcd.clear();
  int res = 0;
  while (oper) {  //Ciclo para introducir la operacion a realizar
    lcd.setCursor(0, 0);
    lcd.print("    Operacion   ");
    lcd.setCursor(0, 1);
    lcd.print(" 1+  2-  3/  4x");
    key = keypad.getKey();
    switch (key) {  //Switch para determinar que operacion a realizar
      case '1':
        res = oper1 + oper2;
        oper = false;
        lcd.clear();
        break;
      case '2':
        res = oper1 - oper2;
        oper = false;
        lcd.clear();
        break;
      case '3':
        res = oper1 / oper2;
        oper = false;
        lcd.clear();
        break;
      case '4':
        res = oper1 * oper2;
        oper = false;
        lcd.clear();
        break;
    }
    while (!oper) { //Ciclo para mostrar el resultado de la operacion
      key = keypad.getKey();
      lcd.setCursor(0, 0);
      lcd.print("Resultado:  ");
      lcd.setCursor(0, 1);
      lcd.print(res);
      if (key == '#') { //Tecla de salida del ciclo de resultado
        oper = true;
        limpiar();
      }
    }
    if (key == '#') {//Condicion para salir del ciclo de entrada de operaciones
      oper = false;
      break;
    }
  }
  ready1 = false;
}
