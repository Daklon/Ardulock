#include "nRF24L01.h"
#include <RF24.h>
#include <SPI.h>

#define pinlong 4

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

char pin[pinlong];

//this config and start the radio
void Radioconfig(RF24 radio){
  radio.begin();
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_LOW);
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,rxAddr);

  radio.startListening();
  
}

void setup (){
   Radioconfig(radio);
   Serial.begin(9600);//ESTO ES PARA DEBUG
}


void Descifrar(){
  //función encargada de descifrar el mensaje recibido desde el arduino exterior
  
}

void Comprobar(){
  //función encargada de comprobar si debe o no abrir la puerta
}

void loop (){
  if (radio.available()){
    radio.read( &pin, sizeof(char) * pinlong );
  }
  Serial.println("Recibido");
  for(int i=0;i<pinlong;i++){
    Serial.print(pin[i]);
  }
}

