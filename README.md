# PLA4

En este repositorio tenemos los diferentes ejericios de la PLA4.

## Blink

Diferentes variantes para hacer parpadear el LED interno.

### Blink 

Utiliza millis() en lugar de delay() para calcular los instantes en los que se debe cambiar el estado del LED.

### BlinkInt

En este caso se hace oscilar un PIN. Las oscilaciones de este PIN generan una interrupción. El ISR de esta interrupción se encarga de cambiar el estado del LED.

### BlinkInt2

Una variante del caso anterior. En este caso el PIN que oscila y el que genera la interrupción cuando cambia de estado son diferentes. La conexión entre ambos PIN's se realiza mediante la colocación de un cable que los une.

### BlinkTimer

La oscilación, que en los casos anteriores se controlaba mediante la función millis(), se controla ahora con un Timer / Contador de la MKR. Cuando este contador llega al valor seleccionado (valor que se calcula en función de la frecuencia del reloj del MCU y el periodo deseado) se produce una interrupción. El ISR, como ocurría en el ejemplo anterior, es el responsable de cambiar el estado del LED.

## SerialCmds

Aplicación para Arduino que es capaz de recibir comandos por el puerto serie. Esta primera versión sólo acepta los comandos ON y OFF (como se pide en el enunciado de la PLA) que encienden y apagan respectivamente el LED.

## SerialCmds2

Este caso es muy similar al anterior pero, se modifica ligeramente el código para que también se acepte un nuevo comando: CHG. Este comando cambia el estado del LED.

## SerialCmds3

Esta versión añade a las anteriores tres nuevos comandos. Los caomandos TMP, PRE y HUM devuelven, respectivamente, los valores de temperatura, presión y humedad leídos por los sensores de la MKRENV.

NOTA: Se requiere que la MKR ENV esté conectada para poder acceder a sus sensores. 
