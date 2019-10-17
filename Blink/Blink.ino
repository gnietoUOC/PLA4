#define ON_DURATION 2000
#define OFF_DURATION 1000

boolean status = LOW;
unsigned long offset = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

// Método que avisa cuando se ha producido una 'transición'
boolean needsSwitch() {
  boolean switching = false;

// Compruebo si ha pasado el tiempo de este estado
  if (millis()>=offset) {
    // Si ha pasado el intervalo, cambio el estado, ...
    status = !status;
    // ... calculo cuando debe producirse el siguiente cambio, ...
    offset = millis()+(status? ON_DURATION:OFF_DURATION);
    // ... y me preparo para notificarlo.
    switching = true;  
  }

  return switching;
}

// Ejecuta las acciones requeridas cuando se produce una 'transición'
void doSwitch() {
    digitalWrite(LED_BUILTIN, status);   // Cambio el estado de la salida del LED   
    Serial.print(millis());
    Serial.println(status? " ON":" OFF");
}

// Bucle principal. Limpio. Solo verifica los cambios de estado y
// ejecuta las acciones necesarias cuando se producen.
void loop() {
  
  if (needsSwitch()) {
    doSwitch();
  }
  
  
}
