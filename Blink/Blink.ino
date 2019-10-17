#define ON_DURATION 2000
#define OFF_DURATION 1000

boolean status = LOW;
int offset = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

boolean needsSwitch() {
  boolean switching = false;
  int duration = status? ON_DURATION:OFF_DURATION;

  if (millis()>=offset+duration) {
    status = !status;
    offset = millis();
    switching = true;  
  }

  return switching;
}

void loop() {
  
  if (needsSwitch()) {
    digitalWrite(LED_BUILTIN, status);   // Cambio el estado de la salida del LED   
    Serial.print(millis());
    Serial.println(status? " ON":" OFF");
  }
  
  
}
