/*
  RGB Controller

  Utiliza transistores NPN para regular el color de LEDs RGB mediante dos botones. 
  Utiliza tres salidas PWM y dos entradas digitales.

  Hay dos botones, el botón "MODE", y el botón "LEVEL".

    -Pulsando el botón "MODE" permutamos el color que queremos cambiar, por defecto
     esta configurado como "R", el canal rojo, si lo pulsamos, pasa a "G", verde,
     y si pulsamos de nuevo pasa a "B", azul. Si pulsamos de nuevo, vuelve a rojo.

    -Pulsando el botón "LEVEL", aumentamos el nivel PWM (el brillo) del canal que
     este seleccionado con "MODE" (rojo, verde o azul). Por defecto es 0 en todos
     los canales.

     Cada pulsación añade 15 puntos de intensidad hasta un valor máximo de 255.
     Al llegar al brillo máximo (255), si pulsamos de nuevo el botón "LEVEL, el 
     valor volverá a 0, apagado.

  Materiales:
  - 3x Transistor NPN (adecuado a la potencia de nuestros LEDs).
  - 2x Resistencia 10K (valor aproximado, 3K-20K también sirven).
  - 2x Botón momentáneo.
  - LED RGB de ánodo común.
  - Fuente de alimentación externa de mismo voltaje que los LEDs RGB y
    suficiente amperaje.
  - Placa de prototipado o similar para colocar los componentes.
  - Variedad de cables de conexión.
 
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

    
  Creado en 2018
  por ComandanteJ (José Carlos Gadea Doncel)

  Código, instrucciones, esquemas e imágenes disponibles 
  en https://github.com/ComandanteJ/PlacaRGB

*/

// -ATENCION-
// En esta version del codigo he incluido comunicacion serial para poder ver en tiempo real como funciona
// el codigo, los valores exactos que estan siendo aplicados, etc.
// Cualquier comando empezado por "Serial." existe para tal fin y por lo tanto no comentare su funcion en
// el codigo.

// Variables constantes, definen el numero de pin.
const int modePin = 2;     // pin del boton "MODE"
const int levelPin = 4;      // pin del boton "LEVEL"
const int redPin = 11,greenPin = 10,bluePin = 9; //pines de salida para cada canal de color. Por defecto, 0 (apagado).

// Variables que pueden cambiar:
int R = 0,G = 0,B = 0; // Estas variables se usaran para controlar el brillo de cada canal
char color = 'R'; // Esta variable controla que canal estamos configurando. Por defecto, el Rojo

void setup() {
  
  // Inicialización de cada pin de salida.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Inicialización de cada pin de entrada.
  pinMode(modePin, INPUT);
  pinMode(levelPin, INPUT);

  Serial.begin(9600);
  Serial.print("--READY--\n");
  
}

void loop() {

  // Primero, el programa busca si hemos pulsado (señal HIGH) el boton "MODE".
  if( digitalRead(modePin) == HIGH ) {

    Serial.print("Boton MODO\n");

    // En caso positivo, comprueba la letra de la variable de control "color".
    // Una vez encuentra el color, lo cambia por el siguiente en la secuencia.
    // Si llega al ultimo color ('B'), vuelve a poner el primero ('R').
    
    if( color == 'R' ) {

      color = 'G';
      Serial.print("Cambio de color: R > G\n");
      
    }else if( color == 'G' ) {

      color = 'B';
      Serial.print("Cambio de color: G > B\n");
      
    }else if( color == 'B' ) {

      color = 'R';
      Serial.print("Cambio de color: B > R\n");
      
    }
    
    // Se añade un retraso para evitar pulsaciones multiples.
    delay(400);
  }

  // Ahora, el programa busca si hemos pulsado (señal HIGH) el boton "LEVEL".
  if(digitalRead(levelPin) == HIGH) {

        // En caso positivo, busca el valor de la variable de control "color", y a continuacion 
        // comprueba que la variable no este en su valor maximo de 255. Si no lo esta, le suma
        // 15. Si esta al maximo, la pone a 0 (apaga esa linea).
        // Por ultimo, escribe la informacion al pin correspondiente y añade un delay para controlar
        // dobles pulsaciones.
        
        if(color == 'R') {
          
          if(R != 255) {
            R+= 15;
          }else {
            R = 0;
          }
          
          analogWrite(redPin, R);
          delay(400);
          
        }else if(color == 'G') {
          
          if(G != 255) {
            G+=15;
          }else {
            G = 0;
          }
          
          analogWrite(greenPin, G);
          delay(400);
          
        }else if(color == 'B') {
          
          if(B != 255) {
            B+=15;
          }else {
            B = 0;
          }
          
          analogWrite(bluePin, B);
          delay(400);
          
        }
        
        Serial.print("Boton NIVEL\n");
        Serial.print("-- R: ");
        Serial.print(R);
        Serial.print("-- G: ");
        Serial.print(G);
        Serial.print("-- B: ");
        Serial.print(B);
        Serial.print("\n");
        
        // Se añade un delay final entre cada bucle para no sobrecargar la lógica.
        delay(200);
  }
}
