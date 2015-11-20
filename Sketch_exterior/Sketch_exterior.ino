#include <avr/sleep.h>

void setup() {
  // put your setup code here, to run once:
  int pin[4] = {1,2,3,4};
  //con input_pullup se invierten los valores, LOW es alto y HIGH es bajo, además al conectarlo a un OUTPUT, este debe estar en LOW
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(13,OUTPUT);//para el led de control (ESTO HAY QUE BORRARLO!!!)
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13,LOW);
}

void firmar(int pin[4]){
//firma el pin introducido
  
}

void cifrar(int pin[4]){
//cifra el pin introducido
  
}
//******************************************************
//esto son solo pruebas para entender como funciona todo
//******************************************************
void leer(){
  sleep_disable();//bit de sleep a 0, no se puede poner en modo sleep
  detachInterrupt(digitalPinToInterrupt(2));//quito la interrupción
  if(digitalRead(2) == LOW){//si se pulsa el pin 2
    digitalWrite(13,LOW);//se apaga el led
  }else{
    digitalWrite(13,HIGH);//si no, se enciende
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  sleep_enable();//establecemos a 1 el bit para poder entrar ne modo sleep
  attachInterrupt(digitalPinToInterrupt(2),leer,FALLING);//fijamos la interrupción para despertar
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//establecemos el modo de mas ahorro de energía
  cli();//bloqueo interrupciones para que no se activen mientras desactivo el BOD
  sleep_bod_disable();//desactivo BOD
  sei();//reactivo interrupciones
  sleep_cpu();//activo el modo sleep
  leer();//al volver a la ejecución normal, ejecuto esta función
}
