# PlacaRGB

Este proyecto usa una placa Arduino con micro-controlador ATmega328.
Esta placa se usara para controlar una tira de LEDs RGB 5050, con dos botones.

# Funcionamiento

La placa usara dos botones que serviran para cambiar el color a configurar (1) y la intensidad de ese color, en 17 pasos (2).

Se usaran señales PWM para variar la intensidad de cada uno de los tres canales R, G y B de la tira LED, con un positivo comun de 12v y un negativo por cada canal.

Se instalara un conector Molex de 12v de 4 pines para dar correitne tanto a la placa Arduino como a la tira LED.

Para encender y apagar cada canal se usaran transistores NPN de alta corriente.

Se usan 17 pasos porque la señal PWM del Arduino tiene 255 valores, y 255 / 17 = incrementos de 15 puntos por cada presion del boton.

# Prototipos

--0.1

El primer prototipo se realiza con una placa Arduino UNO, y las conexiones se realizan mediante breadboard.

Se usan transistores NPN rescatados de una fuente de alimentacion antigua, y tan solo un boton para comprobar el funcionamiento de estos y la tira LED. Pueden verse imagenes del prototipo 0.1 en la carpeta correspondiente.

Realizo un proyecto en java para practicar el codigo que usare en Arduino. Usare el IDE de Arduino, que utiliza C++ (o muy parecido) para programar.

--0.2

En este prototipo uso los mismos materiales y componentes, tres transistores NPN conectados a una placa Arduino Uno y a una tira LED 5050 de ánodo comun.

Esta vez conecto cada canal a su propia salida PWM en la placa Arduino. Esto posibilita variar la intensidad en un total de 255 pasos entre apagado y totalmente encendido.

Tambien he añadido un boton mas, para un total de dos botones, botón "MODE", y botón "LEVEL".
