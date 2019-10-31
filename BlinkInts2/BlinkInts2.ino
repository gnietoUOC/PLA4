#define FLAG 4
#define INTPIN 8
#define DELAY 1000

// Variable que controla el estado del LED. Su valor solo cambia
// dentro de la rutina de interrupción. 
volatile boolean state1 = LOW;

// Valor que controla la oscilación en un PIN y cuyas variaciones
// disparan una interrupción
boolean state2 = LOW ;

// Variable que controla el instante de la próxima oscilación
unsigned long offset=0;


// Defino los puertos y asocio la interrupción a la invocación 
// del método blink.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(FLAG, OUTPUT);
  pinMode(INTPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTPIN), blink, RISING);

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
  needsSwitch();

//  track();  
}

// Simulación de la oscilación en el PIN
void needsSwitch() {
  if (millis()>=offset) {
    state2=!state2;
    digitalWrite(FLAG, state2);
    offset = millis()+DELAY;
    track();  
  }
}

// Rutina que cambia el estado del LED cuando es invocada como 
// consecuencia de la llegada de una interrupción
void blink() {
  state1 = !state1;
}

// Monitoriza el valor de los dos flags
void track() {
  Serial.print(millis());
  Serial.print(state1? " ON ":" OFF ");
  Serial.println(state2? " ON ":" OFF ");
}
