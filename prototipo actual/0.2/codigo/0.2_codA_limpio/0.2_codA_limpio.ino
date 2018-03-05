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
const int redPin = 11,greenPin = 10,bluePin = 9;


int R = 0,G = 0,B = 0; // Estas variables se usaran para controlar el brillo de cada canal
char color = 'R'; // Esta variable controla que canal estamos configurando. Por defecto, el Rojo

void setup() {
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(modePin, INPUT);
  pinMode(levelPin, INPUT);
}

void loop() {

  // Primero, el programa busca si hemos pulsado (señal HIGH) el boton "MODE".
  if( digitalRead(modePin) == HIGH ) {

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
        delay(200);
  }
}
