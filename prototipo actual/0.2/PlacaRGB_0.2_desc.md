# PlacaRGB v0.1
 En este prototipo uso los mismos materiales y componentes, tres transistores NPN conectados a una placa Arduino Uno y a una tira LED 5050 de �nodo comun. 
 
 Esta vez conecto cada canal a su propia salida PWM en la placa Arduino. Esto posibilita variar la intensidad en un total de 255 pasos entre apagado y totalmente encendido.
 
 Tambien he a�adido un boton mas, para un total de dos botones, bot�n "MODE", y bot�n "LEVEL".

    -Pulsando el bot�n "MODE" permutamos el color que queremos cambiar, por defecto
     esta configurado como "R", el canal rojo, si lo pulsamos, pasa a "G", verde,
     y si pulsamos de nuevo pasa a "B", azul. Si pulsamos de nuevo, vuelve a rojo.

    -Pulsando el bot�n "LEVEL", aumentamos el nivel PWM (el brillo) del canal que
     este seleccionado con "MODE" (rojo, verde o azul). Por defecto es 0 en todos
     los canales.

     Cada pulsaci�n a�ade 15 puntos de intensidad hasta un valor m�ximo de 255.
     Al llegar al brillo m�ximo (255), si pulsamos de nuevo el bot�n "LEVEL, el 
     valor volver� a 0, apagado.
 
 El codigo es muy simple pero no esta basado en ningun otro. Pongo a disposicion de quien lo quiera dos versiones, una limpia sin apenascomentarios, y otra muy comentada y con mensajes via monitor en serie implementados, para debug o aprendizaje.
 
 Estos estan en la carpeta "codigo", como "0.2_CodA_limpio" y "0.2_CodA_comentado".
 
# El circuito

 El circuito:
  - La base de cada transistor debe ir conectada a la salida PWM correspondiente
    del Arduino. Rojo = pin 11; Verde: pin 10; Azul: pin 9.

  - El colector de cada transistor debe de ir conectado al c�todo (negativo)
    correspondiente a cada canal del LED RGB.
    
  - El emisor de cada transistor debe de ir conectado a tierra (GND).

  - El LED (o tira LED) RGB debe tener conectado su �nodo (positivo) al
    positivo de la fuente de alimentaci�n externa.

  - Cada bot�n deber� tener conectado uno de sus lados a la salida +5v del Arduino.
    
    El otro lado deber� ir conectado a tierra (GND) y al pin de entrada digital
    correspondiente, pin 2 para el bot�n "MODE" y pin 4 para el bot�n "LEVEL". 

  - Cada pin de entrada digital deber� tener conectado, ademas, una resistencia de 10K
    que ira a tierra (GND).

  - Conectamos la tierra (negativo) de la fuente de alimentaci�n de los LEDs a una tierra
    del Arduino. Si la fuente es de entre 6 y 12 voltios, podemos alimentar el Arduino
    directamente mediante el pin "VIN", conect�ndolo al positivo de la fuente de alimentaci�n.
 
# Materiales

-- 3x Transistor NPN (1x C5027 & 2x C4106), provenientes de una fuente de alimentaci�n ATX antigua.

-- 2x Resistencias (1x 3.3K & 1x 10K). Deber�an ser ambas iguales, pero cumplen su cometido.

-- 2x Bot�n moment�neo tipo PC.

-- 1x Disipador para 3 transistores (NO NECESARIO).

-- 1x Cinta de LEDs RGB 5050 de �nodo com�n con conector RGB, 5m.

-- 1x Fuente de alimentaci�n 12v 7.5A (90W).

-- 1x Placa prototipado.

-- 1x Arduino UNO (cl�nico).

-- Surtido de cables tipo "jumper" para interconexion de componentes.