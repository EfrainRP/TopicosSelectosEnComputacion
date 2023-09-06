//Inicializacion de los valores a utilizar, como de pines y el estado
int state=0;
int LedPin=2;
int PushPin=3;

void setup() {
  //Configuracion de los pines
  pinMode(LedPin, OUTPUT);
  pinMode(PushPin, INPUT);
}

void loop() {
  //Ciclo que estara almacenando un nuevo estado del boton para el led
  state = digitalRead(PushPin); //Recibe lectura del boton pasandola como un estado 
  digitalWrite(LedPin, state);   // Escribe el estado del boton al led
}
