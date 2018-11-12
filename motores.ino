#include <Ultrasonic.h>

  
int derecha1= 23; 
int derecha2= 22;
const int S0 = 12;  
const int S1 = 13;  
const int S2 = 11;  
const int S3 = 10;  
const int out = 9;  
int frecuenciaRoja = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int rojo = 0;
int azul = 0;
int verde = 0;
int LEDA=27;
int LEDV=26;
int LEDR=29;
char color = '0';
int izquierda1= 24; 
int izquierda2= 25;
//FRENTE
const int Trigger1 = 44;  
const int Echo1 = 45;
//DERECHA   
const int Trigger3 = 46;  
const int Echo3 = 48;   //Pin digital 3 para el echo del sensor
//IZQUIERDA   
const int Trigger2 = 50;   //Pin digital 2 para el Trigger del sensor
const int Echo2 = 52;   //Pin digital 3 para el echo del sensor

int potenciamotor1=2;
int potenciamotor=3;
int fase=1;
int rampa=0;
bool derecha=false;
int count=0;
int primerCuenta = 0;
int segundaCuenta = 0;

void setup()
{
  Serial.begin(9600);
  pinMode (derecha1, OUTPUT);   
  pinMode (derecha2, OUTPUT);   
  pinMode (izquierda1, OUTPUT);   
  pinMode (izquierda2, OUTPUT);  
  pinMode(potenciamotor,OUTPUT);
    pinMode(potenciamotor1,OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
   pinMode(out, INPUT);
   digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
   pinMode(LEDR, OUTPUT);
  pinMode(LEDV, OUTPUT);
  pinMode(LEDA, OUTPUT);
 

  pinMode(Trigger1, OUTPUT); //pin como salida
  pinMode(Echo1, INPUT);  //pin como entrada
  pinMode(Trigger2, OUTPUT); //pin como salida
  pinMode(Echo2, INPUT);  //pin como entrada
  pinMode(Trigger3, OUTPUT); //pin como salida
  pinMode(Echo3, INPUT);  //pin como entrada

}
void cambiarpotenciamotores(int x,int dif){

    analogWrite(potenciamotor,x);
    
    analogWrite(potenciamotor1,x-dif);
  
}
void avanzar(){

  cambiarpotenciamotores(125,40);
   digitalWrite(derecha1, HIGH);
   digitalWrite(derecha2, LOW);
   digitalWrite(izquierda2, LOW);
   digitalWrite(izquierda1, HIGH);
   delay(950);
  
}
void avanzarFase2(){

  cambiarpotenciamotores(90,18);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);

  
}
void atras(){
  
   cambiarpotenciamotores(125,40);
  
   digitalWrite(derecha1, LOW);
   digitalWrite(derecha2, HIGH);
   digitalWrite(izquierda2, HIGH);
   digitalWrite(izquierda1, LOW);
  delay(950);
}
void giroejeL(){
  
      /*cambiarpotenciamotores(0,0);
    delay(1000);
    */
    cambiarpotenciamotores(250,80);
  // cambiarpotenciamotores(170,-80);
   digitalWrite(derecha2, HIGH);
   digitalWrite(derecha1, LOW);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
   delay(538);
   
   
   /* while(getDistanceF()<25){
    cambiarpotenciamotores(240,0);
    }ffase
   
   delay(300); 
    avanzar();
    */
}
void giroejeR(){
  
    
   cambiarpotenciamotores(170,-80);
   
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, LOW);
   digitalWrite(izquierda2, HIGH);
   delay(538);
  /*while(getDistanceF()<25){
   cambiarpotenciamotores(240,0);
    }
   delay(300); 
    avanzar();
    */
}

int Detener(){
  cambiarpotenciamotores(0,0);
   delay(1000);
}

boolean atras1=false;
void MovimientoUnidadDelayFASE1(){

   if(getDistanceF()>10){
   avanzar();
    Detener();  
 }
 
 
    if(getDistanceF()<=10){
      Detener();
      
      if((getDistanceL()<8) && (getDistanceR()<8)){
        giroejeR();
        Detener();
        }
        
        else if(getDistanceL()<8){
          
          giroejeR();
          Detener();
          
          }
          
          else{
            giroejeL();
             Detener();   
           }
    }

}
void MovimientoUnidadDelay(){

   if(getDistanceF()>15 && getDistanceR()<18){
    
   avanzar();
 }else if(getDistanceF()>15 && getDistanceR()>17){
   giroejeR();
        Detener();
          avanzar();
           Detener();
        return;
  }
 
 
    Detener();  
 
 
    if(getDistanceF()<=15){
      
      
      if((getDistanceL()<15) && (getDistanceR()<15)){
        giroejeR();
        Detener();
        }
        
        else if(getDistanceL()<getDistanceR()){
          if(getDistanceL()<20){
            atras1=true;
            }
            Serial.println("HOLAAA");
            Serial.println(getDistanceL());
          giroejeR();
          Detener();
          if(atras1){
            atras1=false;
            atras();
             Detener();
            }
          }
          
          else{
             if(getDistanceR()<20){
            atras1=true;
            }
             Serial.println("HOLAAA");
            Serial.println(getDistanceR());
            giroejeL();
             Detener();
               if(atras1){
            atras1=false;
            atras();
             Detener();
            }   
           }
    }

}



int getDistance(int t1,int ec1){
     long t; //timepo que demora en llegar el eco
      long d; //distancia en centimetros
      //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
       delayMicroseconds(2);  
      digitalWrite(t1, HIGH);
      delayMicroseconds(10);     //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
      
      t = pulseIn(ec1, HIGH); //obtenemos el ancho del pulso
       d = t/59; 
       return d;
  }
  int getDistanceF(){
     return getDistance(Trigger1,Echo1);
    }
    int getDistanceR(){
     return getDistance(Trigger2,Echo2);
    }
    int getDistanceL(){
     return getDistance(Trigger3,Echo3);
    }

    void calibrarcolor(){
     //CALIBRACION
        
         //COLOR ROJO 
         
           digitalWrite(S2,LOW);
           digitalWrite(S3,LOW);
         
           frecuenciaRoja = pulseIn(out, LOW);
         
           Serial.print(" R = ");
           Serial.print(frecuenciaRoja);
           delay(500);
        
          //VERDE
          
           digitalWrite(S2,HIGH);
           digitalWrite(S3,HIGH);
        
           frecuenciaVerde = pulseIn(out, LOW);
           
           Serial.print(" V = ");
           Serial.print(frecuenciaVerde);
           delay(500);
        
          //AZUL
           digitalWrite(S2,LOW);
           digitalWrite(S3,HIGH);
          
           frecuenciaAzul = pulseIn(out, LOW);
           
           Serial.print(" A = ");
           Serial.println(frecuenciaAzul);
           delay(500);
        
          // Constrains??
            }
    char getColor(){
          digitalWrite(S2,LOW);
          digitalWrite(S3,LOW);
          
          // Se lee el valor de la frecuencia 
          frecuenciaRoja = pulseIn(out, LOW);
          
         // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaRoja>80 || frecuenciaRoja<35){
          rojo = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaRoja>=35 && frecuenciaRoja<=80){
          rojo  = map(frecuenciaRoja,35,80,255,0);
         }
        
          // Ajustando los filtros verdes de los fotodiodos para que sean leídos 
          digitalWrite(S2,HIGH);
          digitalWrite(S3,HIGH);
         
          // Se lee el valor de la frecuencia 
        frecuenciaVerde = pulseIn(out, LOW);
        
         // Filtro para que no tome valores más grandes que los máx y mínimos
          if(frecuenciaVerde>106 || frecuenciaVerde<42){
          verde = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaVerde>=42 && frecuenciaVerde<=106){
          verde = map(frecuenciaVerde,42,106,255,0);
         }
         
          // Ajustando los filtros azules de los fotodiodos para que sean leídos 
          digitalWrite(S2,LOW);
          digitalWrite(S3,HIGH);
          
          // Se lee el valor de la frecuencia
          frecuenciaAzul = pulseIn(out, LOW);
        
        // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaAzul>122 || frecuenciaAzul<50){
          azul = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaAzul>=50 && frecuenciaAzul<=122){
          azul = map(frecuenciaAzul,50,122,255,0);
         }

      if (frecuenciaAzul>=52 && frecuenciaAzul<=105 && frecuenciaVerde>=27 && frecuenciaVerde<=72 && frecuenciaRoja>=19 && frecuenciaRoja<=50){
         Serial.println("¡Color Amarillo!");
            color = 'y';
            
              digitalWrite(LEDA,HIGH);
            digitalWrite(LEDV,HIGH);
            return color;
         }
       /* 
        Serial.print(" R = ");
         Serial.print(rojo);
          Serial.print("  ");
         
         Serial.print(" A = ");
         Serial.print(azul);
          Serial.print("  ");
         
         Serial.print(" V = ");
         Serial.print(verde);
         */
        //Impresion de los valores de cada color
         
          digitalWrite(LEDR,LOW);
           digitalWrite(LEDA,LOW);
            digitalWrite(LEDV,LOW);
            
               if (rojo>azul && rojo>verde){
                digitalWrite(LEDR,HIGH);
          Serial.println("¡Color Rojo!");
          color = 'r';
          delay(200);
          }
          
          if (azul>rojo && azul>verde){
            digitalWrite(LEDA,HIGH);
            Serial.println("¡Color Azul!");
            color = 'a';
              delay(200);
              
          }
          
          if (verde>rojo && verde>azul){
            digitalWrite(LEDV,HIGH);
            Serial.println("¡Color Verde!");
            color = 'v';
              delay(200);
          }
          
          if(azul==rojo && rojo==verde && rojo==0){
             digitalWrite(LEDV,HIGH);
              digitalWrite(LEDA,HIGH);
              color = 'n';
             //  digitalWrite(LEDR,HIGH);
            }

          
            return color;
    }
 
int sensorlinea(){
  Serial.print("Lectura: ");
  Serial.println(analogRead(A0));
  return (analogRead(A0)); //Imprime el valor de la lectura del canal A0
  //delay(2000); //retardo de 2 segundos entre lectura
  
 }      
bool sensorbola(){
   
        return false;
          
}


void loop()
{ 
 // LDR();
 // return;

  if(getColor()=='v'){
    fase=2;
    }else if(sensorlinea()>600){
     fase=3;
      }else{
        fase=1;
        }

 Serial.println("Fase: ");
 Serial.print(fase);
 
  if(fase==1){
      avanzar();
      Detener();
        if(sensorbola()){
            giroejeR();
        }
        else{
          giroejeL();
        }
          Detener();
      while(getColor()!='v') {
        MovimientoUnidadDelayFASE1();
     //   Detener();  
            
      }
           fase++;
  }
  Serial.println("Fase: ");
 Serial.print(fase);
  while(fase==2){
    
      Detener();
      
          if(sensorlinea()>500){
               if(getDistanceL()< getDistanceR()){
                  giroejeR();
                  avanzar();
                  giroejeL();
               }
               else{
                  giroejeL();
                  avanzar();
                  giroejeR();
               }
          }
          else{
             avanzarFase2();
          } 
          
 }
 Serial.println("Fase: ");
 Serial.print(fase);
    while(fase==3){
      Detener();
      MovimientoUnidadDelay();

      if(getColor()=='r'){
          rampa=1;
          giroejeR();
          break;
      }
   }
cambiarpotenciamotores(200,50);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);

}
