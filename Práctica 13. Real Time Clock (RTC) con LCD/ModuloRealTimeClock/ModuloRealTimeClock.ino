#include <LiquidCrystal.h>;
#include <Wire.h>
#include "RTClib.h"
#include <string.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

RTC_DS1307 rtc;  //Instancia del RTC

DateTime HoraFecha;  //Variable de tiempo y fecha para el RTC

String fecha = " ", hora = " ";  //Cadenas para la fecha y hora

void setup() {
  Serial.begin(9600);  //Inicializamos el monitor serial

  rtc.begin();  //Inicializamos el RTC
  Serial.println("Estableciendo Hora y fecha...");
  rtc.adjust(DateTime(__DATE__, __TIME__));
  Serial.println("DS1307 actualizado hora y fecha:");
  Serial.print("Fecha = ");
  Serial.print(__DATE__);
  Serial.print("  Hora = ");
  Serial.println(__TIME__);

  lcd.begin(16, 2);               //Inicializacion de LCD
  lcd.print("RTC Actualizando");  //Impresion de mensage de actualizacion de fecha y hora
  lcd.setCursor(0, 1);
  lcd.print("  Hora y Fecha  ");

  delay(1000);
  lcd.clear();  //Limpieza de LCD
}

void loop() {
  DateTime HoraFecha = rtc.now();  //Obtenemos la hora y fecha actual

  //Almacenamos los datos de fecha y hora del rtc.now() en Strings(cadenas)
  fecha = String(HoraFecha.day()) + "/" + String(HoraFecha.month()) + "/" + String(HoraFecha.year())+ " ";
  hora = String(HoraFecha.hour()) + ":" + String(HoraFecha.minute()) + ":" + String(HoraFecha.second()) + " ";

  //Imprimimos la fecha y hora en el monitor serial
  Serial.print("Fecha: ");
  Serial.println(fecha);
  Serial.print("Hora: ");
  Serial.println(hora);

  //Imprimimos la fecha y hora en pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Fecha: ");
  lcd.print(fecha);
  lcd.setCursor(0, 1);
  lcd.print("Hora:  ");
  lcd.print(hora);

  delay(1000);
}