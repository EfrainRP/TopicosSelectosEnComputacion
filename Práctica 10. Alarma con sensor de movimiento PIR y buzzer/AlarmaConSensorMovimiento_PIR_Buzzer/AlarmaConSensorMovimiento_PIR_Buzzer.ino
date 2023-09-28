int LedPin = 12, BuzzerPin = 9, PirPin = 11;
float frecuencia[3] = {329.63,349.23,392.00};
int cont = 0;

void setup()
{
  pinMode(LedPin, OUTPUT); 
  pinMode(BuzzerPin, OUTPUT);
  pinMode(PirPin, INPUT);
}

void loop()
{
  int p = digitalRead(PirPin) ;
  if(p == HIGH){
    tone(BuzzerPin, frecuencia[cont]); //activa un tono de frecuencia determinada en un pin dado
    digitalWrite(LedPin, HIGH);
    delay(1000);
  }else {
  	noTone(BuzzerPin); 
    digitalWrite(LedPin, LOW);
  }
	cont = (cont<2? cont+1:0);
}