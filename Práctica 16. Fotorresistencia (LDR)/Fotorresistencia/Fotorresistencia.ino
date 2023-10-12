int mallaPotencia = 2;

void setup() {
  pinMode(mallaPotencia, OUTPUT);  //Configuramos el pin 22 para el foco  
}

void loop() {
  int photoRes = analogRead(0); //Guardamos el valor del pin analogico 0

  if (photoRes > 100){  //Si es mayor a 100, encendera el foco
    digitalWrite(mallaPotencia, HIGH);  //Envia un 1 al pin 2 para encender el foco
  }else{
    digitalWrite(mallaPotencia, LOW);   //Envia un 0 al pin 2 para apagar el foco
  }

}
