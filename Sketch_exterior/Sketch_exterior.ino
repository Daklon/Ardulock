#include <avr/sleep.h>
#include "nRF24L01.h"
#include <RF24.h>
#include <SPI.h>

#define pinlong 4

//create a radio object
RF24 radio(9,14);


//pin list:
//vcc 3.3v MUST!
//gnd gnd
//ce 9
//cs 14 (A0)
//sck 13
//MOSI 11
//MISO 12



//Set the addres to this radio
const byte rxAddr[6] = "00001";

//************************
//** Variables globales **
//************************

  char pin[pinlong];
  int index = 0;
  boolean alreadyReaded = false;

//this config and start the radio
void Radioconfig(RF24 radio){
  radio.begin();
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_LOW);
  radio.enableDynamicPayloads();
  radio.openWritingPipe(rxAddr);

  radio.stopListening();
  
}

void setup() {
  // put your setup code here, to run once:
  Radioconfig(radio);
  
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
  
  Serial.begin(9600);//ESTO ES PARA DEBUG
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
char leer(){
  char caracter = 0;
  
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  
  if(digitalRead(2) == LOW){//si se pulsa el pin 2
    caracter = '1';
  }else if(digitalRead(3) == LOW){
    caracter = '4';
  }else if(digitalRead(4) == LOW){
    caracter = '7';
  }else if(digitalRead(5) == LOW){
    caracter = '*';
  }
  
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  
  if(digitalRead(2) == LOW){
    caracter = '2';
  }else if(digitalRead(3) == LOW){
    caracter = '5';
  }else if(digitalRead(4) == LOW){
    caracter = '8';
  }else if(digitalRead(5) == LOW){
    caracter = '0';
  }
  
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  
  if(digitalRead(2) == LOW){
    caracter = '3';
  }else if(digitalRead(3) == LOW){
    caracter = '6';
  }else if(digitalRead(4) == LOW){
    caracter = '9';
  }else if(digitalRead(5) == LOW){
    caracter = '#';
  }
  if (caracter != 0 && !alreadyReaded){
    alreadyReaded = true;
    delay(350);    
    return caracter;
  }else if(caracter == 0){
    alreadyReaded = false;
    return 0;
  }
}

void Enviar(){
  
  if (!radio.write( &pin, sizeof(char) * pinlong )){
       Serial.println(F("failed"));
  }else{
       Serial.println(F("sended")); 
  }
 
  
} 

void restart(){
  sleep_disable();//bit de sleep a 0, no se puede poner en modo sleep
  detachInterrupt(0);//quito la interrupción
}

void hibernar(){
  sleep_enable();//establecemos a 1 el bit para poder entrar ne modo sleep
  attachInterrupt(0,restart,FALLING);//fijamos la interrupción para despertar
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//establecemos el modo de mas ahorro de energía
  cli();//bloqueo interrupciones para que no se activen mientras desactivo el BOD
  //sleep_bod_disable();//desactivo BOD, solo en MEGA, no en UNO
  sei();//reactivo interrupciones
  sleep_cpu();//activo el modo sleep
  
}

void flush(){
    for (int i=0;i< pinlong;i++){
      pin[i]=0;
    }
    index= 0;
}
void loop() {
 char tecla;  
  tecla = leer();
  if (tecla != 0 && tecla != '#' && tecla != '*'){
    if(index < pinlong){
      pin[index]=tecla;
      index++;
    }else if(index == pinlong){
      //funcion enviar
      Serial.println("enviando pin:\n");

      Enviar();
      //funcion flush
      flush();
    }
  }else if(tecla == '#'){
    Enviar();
    flush();
  }else if(tecla == '*'){
    flush();
  }
}
