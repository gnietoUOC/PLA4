#include <Arduino_MKRENV.h>

int status = LOW;                     // Mantengo el status para poder hacer el cambio
boolean sensors = true;

void setup() {

  Serial.begin(9600);

  while (!Serial);

  Serial.println("*** MKR1000 ***");
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    sensors = false;
  }

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
      digitalWrite(LED_BUILTIN, HIGH);                // Encendemos el LED 
    } else {
      if (!cmd.compareTo("OFF")) {
        status = LOW;
        Serial.println("Apagando");
        digitalWrite(LED_BUILTIN, LOW);               // Apagamos el LED 
      } else {
        if (!cmd.compareTo("TMP")) {
          if (sensors) {
            Serial.println("Midiendo Temperatura");
            float temperature = ENV.readTemperature();// Recuperamos la temperatura 
            Serial.print(temperature);
            Serial.println("ºC");
          } else {
            Serial.println("**");
          }
        } else {
          if (!cmd.compareTo("HUM")) {
            if (sensors) {
              Serial.println("Midiendo Humedad");
              float humidity = ENV.readHumidity();           // Recuperamos la humedad 
              Serial.print(humidity);
                Serial.println("%");
            } else {
              Serial.println("**");
            }
          } else {
            if (!cmd.compareTo("PRE")) {
              if (sensors) {
                Serial.println("Midiendo Presión");
                float pressure = ENV.readPressure();         // Recuperamos la presión 
                Serial.print(pressure);
                Serial.println("kPa");
              } else {
                Serial.println("**");
              }
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
    }
  }

}
