int status = LOW;                     // Mantengo el status para poder hacer el cambio

void setup() {

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, status);  // Empiezo con estado conocido del LED

}

void loop() {

  while(Serial.available()) {         // Esperamos a que lleguen caracteres
  
    String cmd= Serial.readString();  // Leemos el comando que nos llega del puerto serie

    cmd.trim();                       // Eliminamos el CR que incluye al final
    
    Serial.print("Comando: ");
    Serial.println(cmd);
    
    if (!cmd.compareTo("ON")) {
      status = HIGH;
      Serial.println("Encendiendo");
      digitalWrite(LED_BUILTIN, HIGH);              // Encendemos el LED 
    } else {
        if (!cmd.compareTo("OFF")) {
          status = LOW;
          Serial.println("Apagando");
          digitalWrite(LED_BUILTIN, LOW);           // Apagamos el LED 
        } else {
          if (!cmd.compareTo("CHG")) {
            status = !status;
            Serial.print("Cambiando ");
            Serial.println(status? "(Encendiendo)":"(Apagando)");
            digitalWrite(LED_BUILTIN, status);      // Cambiamos el estado del LED 
          } else {
            Serial.println("Comando desconocido");  // Comando desconocido
          }
        }
    }
  }

}
