#include <LiquidCrystal.h>;
#include <Keypad.h>
#include <Wire.h>
#include "RTClib.h"
#include <string.h>

RTC_DS1307 rtc;  //Instancia del RTC
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);//Configuracion de pines de LCD 

//Configuracion del teclado matricial
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

DateTime HoraFecha;              //Variable de tiempo y fecha para el RTC
String HORA_on = " ", HORA_off = " ";  //Cadenas para las horas de entradas

String numIN = " ";  //Cadena para introducir numeros del teclado
int len, state = 0;   // Variables para la introduccion de cifras en teclado
int num,hora, minuto, horaON, horaOFF, minutoON, minutoOFF; //Varibales para el tiempo de entrada y el actual

void cifras(char key) {  //Fucnion para obtener los valores del teclado a un numero, junto con el de la confirmacion/*
  switch (key) {
    case '0' ... '9':
      numIN += key;
      len = numIN.length();  //Actualizamos la longitud de la cadena
      num = numIN.toInt();    //Conversion de cadena a entero
      if (num == 0) {         //Limpiamos lcd para evitar basura de visualizacion
        lcd.setCursor(9, 1);
        lcd.print("  ");
      }
      if (len > 2) {  //Reinicia la cadena si pasamos de 2 cifras
        numIN = " ";
      }
      lcd.setCursor(15, 0);
      lcd.print("  ");
      break;
    case '#':  //Tecla de confimacion con el #
      switch (state) {
        case 0:  //Cuando estemos introduciendo la primera cifra
          if (num >= 0 && num < 24) {
            horaON = num;  //Guardara la primera cifra y se reiniciara sus valores para la sig. cifra
            state++;
            lcd.setCursor(15, 0);
            lcd.print("a");
            limpiar();
          } else {
            lcd.setCursor(15, 0);
            lcd.print("e");
          }
          break;
        case 1:  //Cuando estemos introduciendo lo minutos cifra
          if (num > 0 && num < 59) {
            minutoON = num;  //Guardara la primera cifra y se reiniciara sus valores para el sig. estado
            state++;
            lcd.setCursor(15, 0);
            lcd.print("a");
            lcd.setCursor(0, 1);
            lcd.print("                      ");//Limpieza del renglon 2 para la horaOFF
            limpiar();
            HORA_on = String(horaON) + ":" + String(minutoON); 
          } else {
            lcd.setCursor(15, 0);
            lcd.print("e");
          }
          break;
          case 2:  //Cuando estemos introduciendo lo minutos cifra
          if (num >= 0 && num < 24) {
            horaOFF = num;  //Guardara la primera cifra y se reiniciara sus valores para el sig. estado
            state++;
            lcd.setCursor(15, 0);
            lcd.print("a");
            limpiar();
          } else {
            lcd.setCursor(15, 0);
            lcd.print("e");
          }
          break;
          case 3:  //Cuando estemos introduciendo lo minutos cifra
          if (num > 0 && num < 59) {
            minutoOFF = num;  //Guardara la primera cifra y se reiniciara sus valores para el sig. estado
            state++;
            lcd.setCursor(15, 0);
            lcd.print("a");
            limpiar();
            HORA_off = String(horaOFF) + ":" + String(minutoOFF); 
          } else {
            lcd.setCursor(15, 0);
            lcd.print("e");
          }
          break;
      }
      break;
  }
}

void limpiar() {  //Funcion para limpiar nuestos valores basicas
  numIN = " ";
  num = 0;  //Limpiar resultado para LCD
}
void horaActual() { //Funcion para actualizar la hora y mostrarlo en LCD
  DateTime HoraFecha = rtc.now();  //Obtenemos la hora y fecha actual
  hora = HoraFecha.hour();
  minuto = HoraFecha.minute();
  //Serial.print("Hora: ");
  //Serial.println(String(HoraFecha.hour()) + ":" + String(HoraFecha.minute()) + ":" + String(HoraFecha.second()) + " ");
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  lcd.print(String(HoraFecha.hour()) + ":" + String(HoraFecha.minute()) + ":" + String(HoraFecha.second()) + "      ");
}
void setup() {
  pinMode(22, OUTPUT);  //Configuramos el pin 22 para el foco  
  Serial.begin(9600);  //Inicializacion de monitor Serial
  rtc.begin();         //Inicializamos el RTC
  Serial.println("Estableciendo Hora y fecha...");
  rtc.adjust(DateTime(__DATE__, __TIME__));
  Serial.println("DS1307 actualizado hora y fecha:");
  Serial.print("Fecha = ");
  Serial.print(__DATE__);
  Serial.print("  Hora = ");
  Serial.println(__TIME__);

  lcd.begin(16, 2);  //Inicializando LCD
  lcd.clear();       //Limpiamos la LCD

  delay(1000);
  lcd.clear();  //Limpieza de LCD
}

void loop() {
  char key;                        //Variable que guarda el valor de teclado
  while (state == 0) {  //Ciclo para introducir la hora
    horaActual();
    key = keypad.getKey();
    lcd.setCursor(0, 1);
    lcd.print("Hora ON: ");
    cifras(key);
    if (num) {
      lcd.setCursor(9, 1);
      lcd.print(num);
      lcd.print(":  ");
    }
  }
  while (state == 1) {  //Ciclo para introducir los minutos
    horaActual();
    key = keypad.getKey();
    cifras(key);
    if (num) {
      lcd.setCursor(9, 1);
      lcd.print(String(horaON) + ":");
      lcd.print(num);
      lcd.print("  ");
    }
  }
  while (state == 2) {  //Ciclo para introducir la hora
    horaActual();
    key = keypad.getKey();
    lcd.setCursor(0, 1);
    lcd.print("Hora OFF: ");
    cifras(key);
    if (num) {
      lcd.setCursor(10, 1);
      lcd.print(num);
      lcd.print(":  ");
    }
  }
  while (state == 3) {  //Ciclo para introducir los minutos
    horaActual();
    key = keypad.getKey();
    cifras(key);
    if (num) {
      lcd.setCursor(10, 1);
      lcd.print(String(horaOFF) + ":");
      lcd.print(num);
      lcd.print("  ");
    }
  }
  //(hora >= horaON && minuto >= minutoON) && 
  /*if((hora <= horaOFF && minuto <= minutoOFF)){
    Serial.println(" SIII");
  }
  Serial.print("minutos  ");
  Serial.println(minuto);
  Serial.print("minutosON  ");
  Serial.println(minutoON);*/
  
  ///Se prendera el foco con su temporalizador
  while((hora >= horaON && minuto >= minutoON) && (hora <= horaOFF && minuto < minutoOFF)){
    horaActual();
    lcd.setCursor(0,1);
    lcd.print(" Foco encendido      ");
    digitalWrite(22,HIGH);
    state = 0;
  }
  horaActual();
  
  //Limpieza de basura en LCD
  lcd.setCursor(15, 0);
  lcd.print("  ");
  lcd.setCursor(0,1);
  lcd.print("                     ");
  digitalWrite(22,LOW);
  delay(1000);
}
