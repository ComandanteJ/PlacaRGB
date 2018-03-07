/*
  RGB Controller

  Utiliza transistores NPN para regular el color de LEDs RGB mediante dos botones. 
  Utiliza tres salidas PWM y dos entradas digitales.
    
  Creado en 2018
  por ComandanteJ (José Carlos Gadea Doncel)

  Código, instrucciones, esquemas e imágenes disponibles 
  en https://github.com/ComandanteJ/PlacaRGB

*/

const int modePin = 2;
const int levelPin = 4;
const int redPin = 11,greenPin = 6,bluePin = 9;

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

// Esta funcion recibe un array de enteros con los codigos RGB para cada canal, y
// configura cada canal con estos codigos.
void writeToPins(int RGB[]){
    analogWrite(redPin,RGB[0]);
    analogWrite(greenPin,RGB[1]);
    analogWrite(bluePin,RGB[2]);
  
}

// Esta funcion se encarga de hacer parpadear el color que hemos seleccionado. 
void blink(char col){

  char colChars[3]={'R','G','B'};
  
  int colNums[4]={redPin,greenPin,bluePin,0}; // Array de enteros en el que se incluyen los pines de cada canal RGB, Y espacio para
                                              // almacenar un cuarto pin que sera el que parpadeara.

  // Este FOR se repite tres veces, una por canal de color.
  for(int i = 0; i < 3; i++){


    // Este IF comprueba en cada iteracion del FOR si el valor actual del array colChars es el mismo que el del char que hemos pasado
    // por parametro. Si lo es, recupera esa misma posicion en el array que contiene los pines (colNums), que se corresponde con el pin
    // de ese color, y guarda ese pin en el cuarto valor de dicho array para usarlo mas abajo. Si encuentra coincidencia, 
    // deja de buscar saliendo del FOR con "break".
    if(colChars[i] == col){

      colNums[4] = colNums[i];
      break;
    }
    
  }

    turnOffLeds();

    for(int j = 0;j < 3; j++){

      analogWrite(colNums[4],255);
      delay(200);
      analogWrite(colNums[4],0);
      delay(200);
      
    }

    recoverColor();

    delete[] colChars,colNums;
    
}

void loop() {

  // Primero, el programa busca si hemos pulsado (señal HIGH) el boton "MODE".
  // Se comprueba tambien que el otro boton este en low, para evitar cambiar
  // colores en caso de querer entrar al menu al que se accede mediante la
  // pulsacion silumtanea de ambos.
  if( (digitalRead(levelPin) == LOW)&&(digitalRead(modePin) == HIGH) ) {

    // En caso positivo, comprueba la letra de la variable de control "color".
    // Una vez encuentra el color, lo cambia por el siguiente en la secuencia.
    // Si llega al ultimo color ('B'), vuelve a poner el primero ('R').
    
    if( color == 'R' ) {

      color = 'G';
      
    }else if( color == 'G' ) {

      color = 'B';
      
    }else if( color == 'B' ) {

      color = 'R';
      
    }
    blink(color);
    
    delay(400);
  }

  // Ahora, el programa busca si hemos pulsado (señal HIGH) el boton "LEVEL".
  if((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == LOW)) {

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
        
  }

  // Aqui se comprueba si se han presionado ambos botones a la vez, en cuyo caso entra
  // en el modo de seleccion de colores pre-determinados.
  if((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == HIGH)){

      int tiempo = 0,seleccion=1,cambiar=0,RGB[3];

      turnOffLeds();
      
      for(int i = 0;i < 3;i++){
        analogWrite(bluePin, 200);
        analogWrite(redPin, 0);
        delay(200);
        analogWrite(bluePin, 0);
        analogWrite(redPin, 200);
        delay(200);
      }
  
      turnOffLeds();
      delay(100);

      while(tiempo < 1000){

        while((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == HIGH)){

          if(tiempo >= 1000){
            break;
          }
          
          tiempo += 25;
          
        }

        // Este bucleo salta cuando tenemos solo uno de los botones pulsados, y 
        // su cometido es "navegar" por la variable "seleccion".
        if((digitalRead(levelPin) == HIGH)&&(digitalRead(modePin) == LOW)){

          if(tiempo >= 1000){
            break;
          }

          // Pone la variable "cambiar" a 1 para señalizar que debe cambiarse el color.
          cambiar = 1;

          if(seleccion != 7){

            seleccion += 1;
            
          }else{

            seleccion = 0;
            
          }

          delay(600);
          tiempo = 0; // Se pone el contador de tiempo a 0 despues de cada pulsacion.
          
        }

        // Este bucle es identico al anterior, solo que la seleccion va en sentido contrario.
        if((digitalRead(levelPin) == LOW)&&(digitalRead(modePin) == HIGH)){

          if(tiempo >= 1000){
            break;
          }

          cambiar = 1;
          
          if(seleccion != 0){

            seleccion -= 1;
            
          }else{

            seleccion = 7;
            
          }
          delay(600);
          tiempo = 0;
          
        }

        // Este bucle salta si hemos pulsado solo un boton, y por lo tanto el valor "cambiar" esta a 0.
        if(cambiar == 1){

          // Esta estructura usa el valor de la variable "seleccion" para escribir los tres numeros 
          // R G y B en el array RGB.
          switch(seleccion){
  
            case 0:
              RGB[0]=0;
              RGB[1]=0;
              RGB[2]=0;
              break;
            case 1:
              RGB[0]=255;
              RGB[1]=0;
              RGB[2]=255;
              break;
            case 2:
              RGB[0]=255;
              RGB[1]=128;
              RGB[2]=0;
              break;
            case 3:
              RGB[0]=255;
              RGB[1]=255;
              RGB[2]=0;
              break;
            case 4:
              RGB[0]=128;
              RGB[1]=255;
              RGB[2]=0;
              break;
            case 5:
              RGB[0]=255;
              RGB[1]=255;
              RGB[2]=255;
              break;
            case 6:
              RGB[0]=128;
              RGB[1]=0;
              RGB[2]=128;
              break;
            case 7:
              RGB[0]=139;
              RGB[1]=69;
              RGB[2]=19;
              break;
          }

          // Aqui llamamos a la funcion que recibe el array RGB y escribe los valores en
          // los canales del LED.
          writeToPins(RGB);

          // Por ultimo, pone la variable cambiar a 0 para que no se repita por cada ciclo.
          cambiar = 0;
          
        }
      }   
      
      turnOffLeds();
      for(int i = 0;i < 3;i++){
        analogWrite(bluePin, 200);
        analogWrite(greenPin, 0);
        delay(200);
        analogWrite(bluePin, 0);
        analogWrite(greenPin, 200);
        delay(200);
      }
      recoverColor();
    
  }
}
