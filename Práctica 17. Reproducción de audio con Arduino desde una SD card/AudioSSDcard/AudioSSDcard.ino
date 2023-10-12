#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10

TMRpcm tmrpcm;

void setup() {
  tmrpcm.speakerPin = 9;
  // se definió el pin de salida a la bocina
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println("Inicializando....");
  if (!SD.begin(SD_ChipSelectPin)){  // se checa si la tarjeta está funcionando bien
    Serial.println("SD fail");
    return;

  } else {
    Serial.println("SD ok");
    Serial.println("Playing...");  // se reproduce el audio
    tmrpcm.play("music.wav");
  }
  Serial.println("Finish");
}
void loop() {
}
