#define ON_DURATION 2000
#define OFF_DURATION 1000

boolean status = LOW;
int offset = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  
  if (status) {
    if (millis()>=offset+ON_DURATION) {
      offset = millis();
      digitalWrite(LED_BUILTIN, status);   // Cambio el estado de la salida del LED
      Serial.print(millis());
      Serial.println(" OFF");
      status = !status;
    }
  } else {
    if (millis()>=offset+OFF_DURATION) {
      offset = millis();
      digitalWrite(LED_BUILTIN, status);   // Cambio el estado de la salida del LED   
      Serial.print(millis());
      Serial.println(" ON");
      status = !status;
    }
  }
  
}
