
#include <Arduino.h>
#include "Adafruit_ZeroTimer.h"

#define CLOCK 48000000
#define PERIOD 2 // 1sg

// Objeto que gestionar el temporizador. Utilizamos el temporizador 4
// porque tiene una resolución de 32 bits. Sin esa resolución y con esa 
// velocidad de reloj no podríamos medir más de 1sg. 
Adafruit_ZeroTimer timer = Adafruit_ZeroTimer(4);

// Necesario definir un handler para la interrupción (resetea la 
// interrupción). Usamos el que proporciona la librería.
void TC4_Handler() {
  Adafruit_ZeroTimer::timerHandler(4);
}

//La función que es invocada cuando el contador alcanza el valor
//indicado y que se encargar de controlar el LED.
volatile boolean status = LOW;
void doSwitch() {
  digitalWrite(LED_BUILTIN, status);
  Serial.print(millis());
  Serial.println(status? " ON":" OFF");
  status = !status;
}


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Ajustamos el valor del contador.
  uint32_t compare = PERIOD*48000000/1024;

  timer.enable(false);
  // Ajustamos el valor del prescaler a 1024. Perdemos resolución (no
  // podremos subir de unos 48KHz). En realidad, al poder utilizar 
  // un contador de 32 bits no nos hace falta un prescaler. Lo podríamos 
  // dejas en 1 (ajustando eso sí el valor del contador)
  timer.configure(TC_CLOCK_PRESCALER_DIV1024,   // prescaler
          TC_COUNTER_SIZE_32BIT,                // 32bis
          TC_WAVE_GENERATION_MATCH_PWM          // PWM mode (sea lo que sea)
          );
  timer.setCompare(0, compare);
  // Indicamos la funcion que se debe llamar cuando se produzca la interrupción
  timer.setCallback(true, TC_CALLBACK_CC_CHANNEL0, doSwitch);
  timer.enable(true);
}
      
void loop() {
//  Toda la lógica de esta aplicación está en el callback
}
