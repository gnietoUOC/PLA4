#define FLAG 4
#define DELAY 500

// Variable que controla el estado del LED. Su valor solo cambia
// dentro de la rutina de interrupción. 
volatile boolean state1 = LOW;

// Valor que controla la oscilación en un PIN y cuyas variaciones
// disparan una interrupción
boolean state2 = LOW ;

// Defino los puertos y asocio la interrupción a la invocación 
// del método blink.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(FLAG, INPUT);
  attachInterrupt(digitalPinToInterrupt(FLAG), blink, RISING);

  Serial.begin(9600);
}

// Bucle principal. 
void loop() {

// Unicamente se ajusta el LED en función del valor que haya tomado 
// durante la última interrupción.  
  digitalWrite(LED_BUILTIN, state1);

// Como estamos gestionando la oscilación del PIN desde el mismo
// MKR (no es producida por algún tipo de sensor externo), en 
// este buble también actualizamos su valor.
  digitalWrite(FLAG, state2);
  state2=!state2;
  delay(DELAY);

  track();  
}

void blink() {
  state1 = !state1;
}

// Monitoriza el valor de los dos flags
void track() {
  Serial.print(millis());
  Serial.print(state1? " ON ":" OFF ");
  Serial.println(state2? " ON ":" OFF ");
}
