#include <Arduino_MKRENV.h>

void setup() {

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);


}

void loop() {

  while(Serial.available()) {
  
    String cmd= Serial.readString();// read the incoming data as string

    cmd.trim();
    Serial.print("Comando: ");
    Serial.println(cmd);
    if (!cmd.compareTo(String("ON"))) {
      Serial.println("Encendiendo");
      digitalWrite(LED_BUILTIN, HIGH);   // Encendemos el LED del MKR1000
    } else {
        if (!cmd.compareTo(String("OFF"))) {
          Serial.println("Apagando");
          digitalWrite(LED_BUILTIN, LOW); // Apagamos el LED del MKR1000
        } else {
          Serial.println("Comando desconocido");
        }
    }
  }

}
