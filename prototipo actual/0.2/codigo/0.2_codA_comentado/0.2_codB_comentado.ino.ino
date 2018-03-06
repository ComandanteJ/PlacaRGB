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
	 
	-Pulsando ambos botones a la vez entramos en modo seleccion de color 
	 pre-establecido (los LEDs parpadearan rojo y azul 2 veces para indicar que
	 hemos entrado en el modo).

	 Dentro de este modo, podemos pulsar cualquier boton para movernos por una
	 serie de colores pre-establecidos.

	 Para salir de este modo, se pulsan de nuevo los dos botones a la vez durante
	 un segundo. Los LED parpadearan en azul 2 veces para indicar que hemos salido
	 del modo, y el color volvera al que hubiesemos establecido manualmente.

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
  Serial.print("\n--READY--\n");
  
}

// Esta sencilla funcion apaga todos los LEDs.
void turnOffLeds(){

    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
  
}

// Esta sencilla funcion escribe el valor almacenado en las variables, en los pines.
void recoverColor(){

    analogWrite(redPin,R);
    analogWrite(greenPin,G);
    analogWrite(bluePin,B);
  
}

// Esta funcion se encarga de hacer parpadear el color que hemos seleccionado. 
void blink(char col){

  char colChars[3]={'R','G','B'}; // Array de caracteres con el caracter de cada color, para compararlo con el que viene por parametro.
  
  int colNums[4]={redPin,greenPin,bluePin,0}; // Array de enteros en el que se incluyen los pines de cada canal RGB, Y espacio para
                                              // almacenar un cuarto pin que sera el que parpadeara.


  Serial.print("Caracter col: ");
  Serial.print(col);

  // Este FOR se repite tres veces, una por canal de color.
  for(int i = 0; i < 3; i++){

    Serial.print("\nColor en el for: ");
    Serial.print(colChars[i]);

    // Este IF comprueba en cada iteracion del FOR si el valor actual del array colChars es el mismo que el del char que hemos pasado
    // por parametro. Si lo es, recupera esa misma posicion en el array que contiene los pines (colNums), que se corresponde con el pin
    // de ese color, y guarda ese pin en el cuarto valor de dicho array para usarlo mas abajo. Si encuentra coincidencia, 
    // deja de buscar saliendo del FOR con "break".
    if(colChars[i] == col){

      colNums[4] = colNums[i];
      Serial.print("\nParpadea: ");
      Serial.print(colNums[i]);
      break;
    }
    
  }

    // Llamamos a la funcion que apaga todos los LEDs.
    turnOffLeds();

    // Este FOR itera cuantas veces queramos que parpadeen los LEDs, en este caso, 3 parpadeos. 
    for(int j = 0;j < 3; j++){

      analogWrite(colNums[4],255); // Pone el pin que guardamos antes al maximo de brillo.
      Serial.print("\n");
      Serial.print(colNums[4]); 
      Serial.print(" = ");
      Serial.print(0);
      delay(200); // Espera 200 milisegundos.
      analogWrite(colNums[4],0); // Apaga el pin.
      Serial.print("\n");
      Serial.print(colNums[4]);
      Serial.print(" = ");
      Serial.print(255);
      delay(200); // Espera otros 200ms.
      
    }

    // Lamamos a la funcion que recupera el color que tenian los tres canales antes de ponerlos a 0.
    recoverColor();

    // Antes de salir, borramos de la memoria las variables que hemos creado.
    delete[] colChars,colNums;
    
  
  
}


void writeToPins(int RGB[]){
    Serial.print(RGB[0]);
    Serial.print(RGB[1]);
    Serial.print(RGB[2]);
    analogWrite(redPin,RGB[0]);
    analogWrite(greenPin,RGB[1]);
    analogWrite(bluePin,RGB[2]);
  
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
    // Por ultimo, llamamos a la funcion para hacer parpadear el color que hemos seleccionado.
    blink(color);
    
    // Y se añade un retraso para evitar pulsaciones multiples.
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
        
  }

  if((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == HIGH)){

      Serial.print("\n¡ENTRANDO EN MODO SELECCION DE COLOR!\n");

      int tiempo = 0,seleccion=1,cambiar=0,RGB[3];

      turnOffLeds();

      delay(500);
      
      analogWrite(bluePin, 70);
      analogWrite(redPin, 70);

      while(tiempo < 1000){

        while((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == HIGH)){

          tiempo += 25;
          Serial.print("\nTiempo: ");
          Serial.print(tiempo);
          
        }

        if(digitalRead(levelPin) == HIGH){

          if(tiempo >= 1000){
            break;
          }

          cambiar = 1;

          Serial.print("\nLevelPin. ");
          if(seleccion != 7){

            seleccion += 1;
            
          }else{

            seleccion = 0;
            
          }

          delay(600);
          tiempo = 0;
          Serial.print("\nSeleccion: ");
          Serial.print(seleccion);
          
        }
        
        if(digitalRead(modePin) == HIGH){

          if(tiempo >= 1000){
            break;
          }

          cambiar = 1;
          
          Serial.print("\nModePin. ");
          if(seleccion != 0){

            seleccion -= 1;
            
          }else{

            seleccion = 7;
            
          }
          delay(600);
          tiempo = 0;
          Serial.print("\nSeleccion: ");
          Serial.print(seleccion);
          
        }
        if(cambiar == 1){
          switch(seleccion){
  
            case 0:
            Serial.print("\nCaso 0\n");
              RGB[0]=0;
              RGB[1]=0;
              RGB[2]=0;
              break;
            case 1:
            Serial.print("\nCaso 1\n");
              RGB[0]=255;
              RGB[1]=0;
              RGB[2]=255;
              break;
            case 2:
            Serial.print("\nCaso 2\n");
              RGB[0]=255;
              RGB[1]=128;
              RGB[2]=0;
              break;
            case 3:
            Serial.print("\nCaso 3\n");
              RGB[0]=255;
              RGB[1]=255;
              RGB[2]=0;
              break;
            case 4:
            Serial.print("\nCaso 4\n");
              RGB[0]=128;
              RGB[1]=255;
              RGB[2]=0;
              break;
            case 5:
            Serial.print("\nCaso 5\n");
              RGB[0]=255;
              RGB[1]=255;
              RGB[2]=255;
              break;
            case 6:
            Serial.print("\nCaso 5\n");
              RGB[0]=128;
              RGB[1]=0;
              RGB[2]=128;
              break;
            case 7:
            Serial.print("\nCaso 5\n");
              RGB[0]=139;
              RGB[1]=69;
              RGB[2]=19;
              break;
          }
     
          writeToPins(RGB);
  
          cambiar = 0;
          
        }
      }

      turnOffLeds();
      analogWrite(bluePin, 70);
      delay(200);
      analogWrite(bluePin, 0);
      delay(200);
      analogWrite(bluePin, 70);
      delay(200);
      analogWrite(bluePin, 0);
      delay(200);
      recoverColor();
    
  }















  
}
