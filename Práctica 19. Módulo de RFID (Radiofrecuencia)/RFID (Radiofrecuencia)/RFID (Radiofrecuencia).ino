//Inicializando variables
int count = 0;
char c;
String id;

void setup() {  //Configuracion de programas
  Serial.begin(9600);
  Serial.println("Please scan your RFID TAG: ");
}
//  
void loop() {
  while (Serial.available() > 0) {  //Si recibe algo en la entrada, iniciara el bucle
    c = Serial.read();  //Almacena el caracter recibido
    count++;  //aumenta el contador, para conocer la longitud de la palabra
    id += c;  //se va almacenando los caracteres en la cadena de la palabra
    if (count == 14) {  //Si el contador de la palabra es 14, se analizara el ID 
      Serial.println("El numero de serie de la tarjeta es: ");
      Serial.print(id); //Imprime lo recibido
    
      if (id == "AB 12 34 5B 78") { //Verificacion de ID
        Serial.println("  Valid TAG");
      } else {
        Serial.println("  Invalid TAG");
      }
      count++;
    }
    if(count > 14){
      count = 0;//Reinicia variables para seguir recibiendo datos
      id = "";
    }
  }
  delay(500);
}