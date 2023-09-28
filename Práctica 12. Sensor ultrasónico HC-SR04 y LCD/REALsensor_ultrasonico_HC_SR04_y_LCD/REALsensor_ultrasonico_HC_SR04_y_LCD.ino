#include "rgb_lcd.h" //Libreria de la LCD personal
rgb_lcd lcd;

int trig=9, echo=8;

float t, d; //t=Tiempo	d=Distancia

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  
  lcd.begin(16, 2); //Iniciazlizacion de la pantalla LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dist");
  lcd.setCursor(0,1);
  lcd.print("Coloque objeto");
}

void loop()
{
  /* El sensor ultrasónico funciona por medio de pulsos
que envía al objeto a medir, y la distancia es proporcional
a la duración del pulso, por lo tanto usaremos la ecuación física d=v*t
*/
  digitalWrite(trig, HIGH);	// Establecemos el valor del pin HIGH(5V)
  delayMicroseconds(1000);  // Espera un segundo
  digitalWrite(trig, LOW);	// Valor del pin LOW(0V)
  
  d = pulseIn(echo, HIGH); //Para leer cuando Echo sea HIGH
  d = (d/ 2) / 29.1; //Ecuación
  delay(100);
  // Este sensor es capaz de detectar hasta 5 mts.
	if (d < 500) {// Le damos instrucción para que si es menor de 5 mts continúe
  		if (d < 100) {//Si es menor de 1 m, desplegara la información en cm.
          //Para imprimirlo en el serial monitor:
          Serial.print("Distancia: ");
   
      Serial.println(d);
        //Para imprimirlo en el LCD:
      lcd.setCursor(0,0);
      lcd.print("Dist: ");
      lcd.setCursor(7,0);
      lcd.print(d);
  	  lcd.print("cm");
	}
  
    if (d >= 100){ //Si es mayor a 1 m, lo despliega en mts.
      Serial.print("Distancia: ");
      Serial.print(d);
      Serial.println(" cm");
      //En el LCD
      lcd.setCursor(0,0);
      lcd.print("Dist.: ");
      lcd.setCursor(7,0);
      lcd.print(d/100);
      lcd.print(" m");
    }
  } else {//Si es mayor 5mts, especifique que el objeto esta fuera de rango
    Serial.print("FUERA DE RANGO");
    lcd.setCursor(0,0);
    lcd.print(" FUERA DE RANGO ");
  }
}