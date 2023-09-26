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

char numIN[2]; //Arreglo para introducir numeros del teclado
int pos = 0;
bool op1 = true, oper = false;
int op, oper1, oper2;

int operando (char key){
  if((key!='#') && (pos<2)){
    numIN[pos]=key;
    pos++;
  }  
  if(pos>=2){
    pos=0;
  }
  
  int op = (numIN[1] == ' '? String(numIN[0]).toInt() : (String(numIN[0]).toInt()*10)+String(numIN[1]).toInt());
  Serial.println(op);
  return op;
}
void setup() {
  lcd.begin (16,2); //Inicializando LCD
  lcd.clear();//Limpiamos la LCD
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if(op1){
    lcd.setCursor(0,0);
    lcd.print("Primer Operando: ");
  }else{
    lcd.setCursor(0,0);
    lcd.print("Segundo Operando: ");
  }
  switch(key){
    case '0'...'9':
      if(pos<2){
        numIN[pos++]=key;
      }else {
        pos = 0;
      }
      op = (numIN[1] == ' '? String(numIN[0]).toInt() : (String(numIN[0]).toInt()*10)+String(numIN[1]).toInt());
      break;
    case '#':
      if(op1){
        numIN[0]=' ';
        numIN[1]=' ';
        oper1 = op;
        op1 =false;
      }else {
        numIN[0]=' ';
        numIN[1]=' ';
        oper2 = op;
        oper = true;
      }
      break;
  }
  //int op1 = operando(key);
  lcd.setCursor(0,1);
  lcd.print(op);
  Serial.print("oper1: ");
  Serial.println(oper1);
  Serial.print("oper2: ");
  Serial.println(oper2);
  if(oper){
    int operador=0;
    key = keypad.getKey();
    switch(key){
    case '0'...'9':
      if(pos<1){
        numIN[pos++]=key;
      }else {
        pos = 0;
      }
      operador = String(numIN[0]).toInt();
      break;
    }
    int res = 0;
    float div =0.0;
    switch(operador){
      case '1':
        res = oper1 + oper2;
        Serial.print("res: ");
        Serial.println(res);
        break;
      case '2': 
        res = oper1 - oper2;
        Serial.print("res: ");
        Serial.println(res);
        break;
      case '3':
        div = oper1 / oper2;
        Serial.print("res: ");
        Serial.println(div);
        break;
      case '4':
        res = oper1 * oper2;
        Serial.print("res: ");
        Serial.println(res);
        break;
    }
    
  }
  
}
