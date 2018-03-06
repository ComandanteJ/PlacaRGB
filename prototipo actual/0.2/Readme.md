# PlacaRGB v0.2 - Cod0.2B
 En este prototipo uso los mismos materiales y componentes, tres transistores NPN conectados a una placa Arduino Uno y a una tira LED 5050 de ánodo comun. 
 
 Esta vez conecto cada canal a su propia salida PWM en la placa Arduino. Esto posibilita variar la intensidad en un total de 255 pasos entre apagado y totalmente encendido.
 
 Tambien he añadido un boton mas, para un total de dos botones, botón "MODE", y botón "LEVEL".

    -Pulsando el botón "MODE" permutamos el color que queremos cambiar, por defecto
     esta configurado como "R", el canal rojo, si lo pulsamos, pasa a "G", verde,
     y si pulsamos de nuevo pasa a "B", azul. Si pulsamos de nuevo, vuelve a rojo.

    -Pulsando el botón "LEVEL", aumentamos el nivel PWM (el brillo) del canal que
     este seleccionado con "MODE" (rojo, verde o azul). Por defecto es 0 en todos
     los canales.

     Cada pulsación añade 15 puntos de intensidad hasta un valor máximo de 255.
     Al llegar al brillo máximo (255), si pulsamos de nuevo el botón "LEVEL, el 
     valor volverá a 0, apagado.
     
    -Pulsando ambos botones a la vez entramos en modo seleccion de color 
     pre-establecido (los LEDs parpadearan rojo y azul 2 veces para indicar que
     hemos entrado en el modo).

     Dentro de este modo, podemos pulsar cualquier boton para movernos por una
     serie de colores pre-establecidos.

     Para salir de este modo, se pulsan de nuevo los dos botones a la vez durante
     un segundo. Los LED parpadearan en azul 2 veces para indicar que hemos salido
     del modo, y el color volvera al que hubiesemos establecido manualmente.
 
 El codigo es muy simple pero no esta basado en ningun otro. Pongo a disposicion de quien lo quiera dos versiones, una limpia sin apenascomentarios, y otra muy comentada y con mensajes via monitor en serie implementados, para debug o aprendizaje.
 
 Estos estan en la carpeta "codigo", como "0.2_CodA_limpio" y "0.2_CodA_comentado".
 
# El circuito

 El circuito:
  - La base de cada transistor debe ir conectada a la salida PWM correspondiente
    del Arduino. Rojo = pin 11; Verde: pin 10; Azul: pin 9.

  - El colector de cada transistor debe de ir conectado al cátodo (negativo)
    correspondiente a cada canal del LED RGB.
    
  - El emisor de cada transistor debe de ir conectado a tierra (GND).

  - El LED (o tira LED) RGB debe tener conectado su ánodo (positivo) al
    positivo de la fuente de alimentación externa.

  - Cada botón deberá tener conectado uno de sus lados a la salida +5v del Arduino.
    
    El otro lado deberá ir conectado a tierra (GND) y al pin de entrada digital
    correspondiente, pin 2 para el botón "MODE" y pin 4 para el botón "LEVEL". 

  - Cada pin de entrada digital deberá tener conectado, ademas, una resistencia de 10K
    que ira a tierra (GND).

  - Conectamos la tierra (negativo) de la fuente de alimentación de los LEDs a una tierra
    del Arduino. Si la fuente es de entre 6 y 12 voltios, podemos alimentar el Arduino
    directamente mediante el pin "VIN", conectándolo al positivo de la fuente de alimentación.
 
# Materiales

-- 3x Transistor NPN (1x C5027 & 2x C4106), provenientes de una fuente de alimentación ATX antigua.

-- 2x Resistencias (1x 3.3K & 1x 10K). Deberían ser ambas iguales, pero cumplen su cometido.

-- 2x Botón momentáneo tipo PC.

-- 1x Disipador para 3 transistores (NO NECESARIO).

-- 1x Cinta de LEDs RGB 5050 de ánodo común con conector RGB, 5m.

-- 1x Fuente de alimentación 12v 7.5A (90W).

-- 1x Placa prototipado.

-- 1x Arduino UNO (clónico).

-- Surtido de cables tipo "jumper" para interconexion de componentes.
