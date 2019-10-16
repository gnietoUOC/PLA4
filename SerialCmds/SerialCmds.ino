void setup() {

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {

  while(Serial.available()) {         // Esperamos a que lleguen caracteres
  
    String cmd= Serial.readString();  // Leemos el comando que nos llega del puerto serie

    cmd.trim();                       // Eliminamos el CR que incluye al final
    
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
