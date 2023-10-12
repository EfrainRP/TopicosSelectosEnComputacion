#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10

TMRpcm tmrpcm;
int trig = 7, echo = 6;
float d;
void setup() {
  tmrpcm.speakerPin = 9;
  // se definió el pin de salida a la bocina
  pinMode(9, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  Serial.println("Inicializando....");
  if (!SD.begin(SD_ChipSelectPin)){  // se checa si la tarjeta está funcionando bien
    Serial.println("SD fail");
    return;

  }
}
void loop() {
  digitalWrite(trig, HIGH);  // Establecemos el valor del pin HIGH(5V)
  delayMicroseconds(1000);   // Espera un segundo
  digitalWrite(trig, LOW);   // Valor del pin LOW(0V)

  d = pulseIn(echo, HIGH);  //Para leer cuando Echo sea HIGH
  d = (d / 2) / 29.1;       //Ecuación
  delay(100);
  Serial.print("Dist: ");
  Serial.println(d);
  if (d < 11){
    Serial.println("SD ok");
    Serial.println("Playing...");  // se reproduce el audio
    tmrpcm.play("music.wav");
    while (tmrpcm.isPlaying()) {}
    delay(500);
    tmrpcm.stopPlayback();
  }
}
