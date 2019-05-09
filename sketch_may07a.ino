#include <SPI.h>        

#include <Ethernet.h>

#include <EthernetUdp.h>

#include <DHT.h>
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String temp;
String umid;

//Inserisci qui sotto un indirizzo MAC e un indirizzo IP per il tuo controller

//L'indirizzo IP dipenderà dalla tua rete locale:

byte mac[] = { 0x5C, 0xF9, 0xDD, 0x73, 0x9F, 0xEE };
IPAddress ip(192, 168, 8, 19);



unsigned int localPort = 8888;      // porta locale in ascolto



// Un'istanza EthernetUDP che ci consente di inviare e ricevere pacchetti su UDP

EthernetUDP Udp;



void setup() {

  //inizia l'Ethernet e UDP:

  Ethernet.begin(mac,ip);

  Udp.begin(localPort);

  Serial.begin(9600);

}



void loop() {

  int t = dht.readTemperature();
  int h = dht.readHumidity();
  temp=String(t);
  umid=String(h);
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

    Udp.write("t" + t);
    Udp.write("u" + h);

    Udp.endPacket();

}
