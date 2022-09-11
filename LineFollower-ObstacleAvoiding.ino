int pista=0;
int linea=1;
double d_Objeto=15;
double d_Vuelta=17;
double d_Busqueda=13;

int e1=9; //Echo s.ultrasonico(entrada)
int tr1=8;//Trigger s.ultrasonico(ultrasonico)
int e2=11; //Echo s.ultrasonico(entrada)
int tr2=10;//Trigger s.ultrasonico(ultrasonico)

int n=0;
//Controlador rueda izquierda
int in1=4; 
int in2=2;
int EnA=3; //Velocidad Izquierda

//Controlador rueda derecha
int in3=13;
int in4=12;
int EnB=5; //Velocidad Derecha

double d1=0;
double d2=0;

int USI=6; //S.ultrasonico izquierdo
int USD=7;//S.ultrasonico derecha

int bi; //Variable que guarda el valor bouleano del S.ultrasonico izquierdo
int bd;//Variable que guarda el valor bouleano del S.ultrasonico derecha

int velizq=63;
int velder=70;

void setup() {
 pinMode(tr1,OUTPUT);
pinMode(tr2,OUTPUT);
pinMode(e1,INPUT);
pinMode(e2,INPUT);

pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(EnA,OUTPUT);

pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(EnB,OUTPUT);

pinMode(USI,INPUT);
pinMode(USD,INPUT);



Serial.begin(9600);

}

void loop() {
 d1=Distancia(tr1,e1);

   
 bi=digitalRead(USI);
 bd=digitalRead(USD);
 

 if(d1 <= d_Objeto){ //condicional "Si entonces" para localizar el objeto en la pista
  detenerse();
  delay(300);
  Serial.println("Alto1");
  do{
    d2=Distancia(tr2,e2);
    correcion_derecha();
    Serial.println("Derecha1=");
   
  }while(d2 >= d_Vuelta); //Comenzar a girar hasta que el Sensor 2 esta defrente al objeto
  detenerse();
  delay(300);
  Serial.println("Alto2");
  do{
    d2=Distancia(tr2,e2);
    bi=digitalRead(USI);
    bd=digitalRead(USD);
    Serial.println(bi);
    
while(d2<d_Busqueda){ //en caso de estar muy cerca del objeto, el carro se alejara 
  d2=Distancia(tr2,e2);
  correcion_derecha();
  bi=digitalRead(USI);
  bd=digitalRead(USD);
 
  Serial.println("Derecha2");
  if(bi==linea ){ //Si cualquiera de los sensores encuentra la linea, inmediatamente "romper" el bucle 
    d2=30;

  }else if(bd==linea){
    d2=30;
    bi=linea;
  }
}
while(d2>=d_Busqueda){ //en caso de estar muy lejis del objeto, el carro se acercara
  d2=Distancia(tr2,e2);
  correcion_izquierda();
  bi=digitalRead(USI);
   bd=digitalRead(USD);
  
  Serial.println("Izquierda"); 
  if(bi==linea ){ //Si cualquiera de los sensores encuentra la linea, inmediatamente "romper" el bucle
    d2=1;
    
  }else if(bd==linea){
    d2=1;
    bi=linea;
  }
  
  }
  detenerse();
delay(350);
  if(bi==pista){ //Mientras los sensores no encuentren la pista, despues de que cada vez que el carro haha una correción de dirección, este avanzara para rodear al objeto
  n=0;
 while(n<=110){
  bi=digitalRead(USI);
  bd=digitalRead(USD);
  avanzar();
  delay(1);
  Serial.println(n);
  n++;
  if(bi==linea){

    n=10000;
  }else if(bd==linea){ //Si cualquiera de los sensores encuentra la linea, inmediatamente "romper" el bucle
    n=10000;
    bi=1;
  }else if(d2>=d_Busqueda){ //Si detecta  que el carro esta alejandose del obstaculo, "romper" el bucle para realizar la corección correspondiente
    n=10000;
  }
  
 }

  }
  detenerse();
delay(350);
  
  }while(bi==pista); //Do while que rodea al objeto hasta que llega a la linea; mientras el sensor detecta la pista
bi=digitalRead(USI);
 bd=digitalRead(USD);

 if(bd==linea){ //En caso de que llegue primero el sensor izquierda, realizar un correción para acoplarse a la pista
   do{
    bi=digitalRead(USI);
    bd=digitalRead(USD);
    avanzar();
   }while(bi==pista);
     detenerse();
  delay(300);




 }else if(bi==linea && bd==linea){ //En caso de que ambos sensores sensores lleguen a al mismo tiempo, realizar un correción para acoplarse a la pista
  do{
    correcion_derecha();
  }while(bd==pista);
  detenerse();
  delay(300);
 }
    
  } else if(bi==linea && bd==pista){
    correcion_derecha();
    
  }else if(bi==pista && bd==linea){
    correcion_izquierda();
    
  }else if(bi==linea && bd==linea){
    detenerse();
    
  }else if(bi==pista && bd==pista){
    avanzar();
   
  }
 

}

//formula para calcular la distancia con el ultrasonico en cm
double Distancia(int tr, int e){

  int t=0;
  double d=0;
  digitalWrite(tr,HIGH); //manda la señal por el ultrasonico
  delayMicroseconds(10);//tiempo que se tarda en salir de la señal
  digitalWrite(tr,LOW);//se "apaga" la señal despues de cierto tiempo
  
  t=pulseIn(e,HIGH);//recibe la señal emitida despues de un tiempo y se guarda
  
  d=t/58.2;

  return d;


  
}



 void avanzar(){
  
  analogWrite(EnA,velizq);
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);

  
  analogWrite(EnB, velder);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);




 }

void correcion_izquierda(){

analogWrite(EnA,velizq);
  digitalWrite(in1, HIGH);
  digitalWrite(in2,LOW);

  
  analogWrite(EnB,velder);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

}


void correcion_derecha(){
  analogWrite(EnA,velizq);
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);

  


  analogWrite(EnB,velder);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);


}

void detenerse() {

  digitalWrite(in1, LOW);
  digitalWrite(in2,LOW);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);


}
