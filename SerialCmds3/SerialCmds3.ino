#include <Arduino_MKRENV.h>

const String PROGMEM cmd1 = "ON";
const String PROGMEM cmd2 = "OFF";
const String PROGMEM cmd3 = "CHG";
const String PROGMEM cmd4 = "TMP";
const String PROGMEM cmd5 = "HUM";
const String PROGMEM cmd6 = "PRE";
const String cmds[] PROGMEM = {cmd1,cmd2,cmd3,cmd4,cmd5,cmd6};

int status = LOW;                     // Mantengo el status para poder hacer el cambio
boolean sensors = true;               // Indicador del estado de los sensores

void setup() {

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, status);  // Empiezo con estado conocido del LED

  Serial.println("*** MKR1000 ***");
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    sensors = false;
  }
}

void loop() {

  while(Serial.available()) {         // Esperamos a que lleguen caracteres
  
    String cmd= Serial.readString();  // Leemos el comando que nos llega del puerto serie

    Serial.print("Comando: ");
    Serial.println(cmd);

    int n = checkCmd(cmd);
    if (n<0) {
      Serial.println("Comando desconocido");
    } else {
      processCmd(n);
    }
  }
}

// Comprobamos si se ha introducido un comando válido
int checkCmd(String cmd) {
  int n = -1;
  int i = 0;
  
  // Eliminamos el CR (si lo incluye) del final
  cmd.trim();                       
  
  // Buscamos el ordinal del comando introducido
  do {
    if (!cmd.compareTo(cmds[i])) {
      n = i;
    }
  } while (n<0 && ++i<sizeof(cmds));

  return n;  
}

// Procesamos el comando correspondiente
void processCmd(int n) {
  switch (n) {
    case 0:
      Serial.println("Encendiendo");
      digitalWrite(LED_BUILTIN, HIGH);    // Encendemos el LED del MKR1000
      break;
    case 1:
      Serial.println("Apagando");
      digitalWrite(LED_BUILTIN, LOW);     // Apagamos el LED del MKR1000
      break;
    case 2:
      status = !status;
      Serial.print("Cambiando ");
      Serial.println(status? "(Encendiendo)":"(Apagando)");
      digitalWrite(LED_BUILTIN, status);  // Cambiamos el estado del LED 
      break;
    case 3:
      if (sensors) {
        Serial.println("Midiendo Temperatura");
        float temperature = ENV.readTemperature();// Recuperamos la temperatura 
        Serial.print(temperature);
        Serial.println("ºC");
      } else {
        Serial.println("**");
      }
      break;
    case 4:
      if (sensors) {
        Serial.println("Midiendo Humedad");
        float humidity = ENV.readHumidity();           // Recuperamos la humedad 
        Serial.print(humidity);
          Serial.println("%");
      } else {
        Serial.println("**");
      }
      break;
    case 5:
      if (sensors) {
        Serial.println("Midiendo Presión");
        float pressure = ENV.readPressure();         // Recuperamos la presión 
        Serial.print(pressure);
        Serial.println("kPa");
      } else {
        Serial.println("**");
      }
      break;
  }
}
