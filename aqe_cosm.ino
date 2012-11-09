// Sketch to send data from my Air Quality Egg Shield to Cosm
// Copyright (C) 2012 Sam Mulube
// 
// This sketch will only work on devices that can use the EtherCard library,
// i.e. devices containing the ENC28J60 Ethernet controller. In actuality
// I've only tested this on a Nanode.
//
// Requires:
//  * EtherCard library: https://github.com/jcw/ethercard
//  * DHT Sensor library: https://github.com/adafruit/DHT-sensor-library
//  * EggBus library: http://aqe.wickeddevice.com/wp-content/uploads/2012/10/EggBus.zip

#include <EtherCard.h>
#include <stdint.h>
#include <DHT.h>
#include "Wire.h"
#include "EggBus.h"

EggBus eggBus;

#define DHTPIN 17 // analog pin 3
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

// Change these settings to match your feed and api key
#define FEED "84633"
#define APIKEY "7_t1mU275UovMDS93vVHPMMyFUmSAKxtQnNmK0JWZUlHaz0g"
#define FREQUENCY 20000

// ethernet interface mac address, must be unique on the LAN
byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

char website[] PROGMEM = "api.cosm.com";

byte Ethernet::buffer[700];
uint32_t timer;
Stash stash;
  
uint8_t egg_bus_address;
float i_scaler = 0.0;
uint32_t r0 = 0;
uint32_t measured_value = 0;
  
void setup() {
  Serial.begin(9600);
  Serial.println(F("Air Quality Egg Shield to Cosm - v0.0.1"));
  Serial.println(F("======================================="));
 
  Serial.println(F("Initializing network"));
  Serial.println(F("---------------------------------------"));
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println("  Failed to access Ethernet controller");
  if (!ether.dhcpSetup())
    Serial.println("  DHCP failed");

  ether.printIp("  IP:  ", ether.myip);
  ether.printIp("  GW:  ", ether.gwip);  
  ether.printIp("  DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website))
    Serial.println("  DNS failed");
    
  ether.printIp("  SRV: ", ether.hisip);
  Serial.println(F("---------------------------------------"));
}

void loop() {
  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
    timer = millis() + FREQUENCY;
    
    eggBus.init();
    byte sd = stash.create();
    
    // Capture the gas sensors from the egg bus
    // Note we're not capturing the units or resistance of the sensors here
    while((egg_bus_address = eggBus.next())) {
      uint8_t numSensors = eggBus.getNumSensors();
      for(uint8_t ii = 0; ii < numSensors; ii++) {
        Serial.print(eggBus.getSensorType(ii));
        stash.print(eggBus.getSensorType(ii));
        Serial.print(",");
        stash.print(",");
        Serial.println(eggBus.getSensorValue(ii), 4);
        stash.println(eggBus.getSensorValue(ii), 4);
      }
    }
    
    // Capture our analog temp and humidity sensors
    
    Serial.print("Humidity,");
    stash.print("Humidity,");
    float currHumidity = getHumidity();
    Serial.println(currHumidity, 2);
    stash.println(currHumidity, 2);
    
    Serial.print("Temperature,");
    stash.print("Temperature,");
    float currentTemp = getTemperature();
    Serial.println(currentTemp, 2);
    stash.println(currentTemp, 2);
    
    stash.save();
    
    // generate the header with payload - note that the stash size is used,
    // and that a "stash descriptor" is passed in as argument using "$H"
    Stash::prepare(PSTR("PUT http://$F/v2/feeds/$F.csv HTTP/1.0" "\r\n"
                        "Host: $F" "\r\n"
                        "X-ApiKey: $F" "\r\n"
                        "Content-Length: $D" "\r\n"
                        "\r\n"
                        "$H"),
                        website,
                        PSTR(FEED),
                        website, 
                        PSTR(APIKEY), 
                        stash.size(), 
                        sd);

    // send the packet - this also releases all stash buffers once done
    ether.tcpSend();
    
    Serial.println(F("---------------------------------------"));
  }
}

//--------- DHT22 humidity ---------
float getHumidity(){
  float h = dht.readHumidity();
  if (isnan(h)){
    //failed to get reading from DHT    
    delay(2500);
    h = dht.readHumidity();
    if(isnan(h)){
      return -1; 
    }
  } 
  else return h;
}

//--------- DHT22 temperature ---------
float getTemperature(){
  float t = dht.readTemperature();
  if (isnan(t)){
    //failed to get reading from DHT
    delay(2500);
    t = dht.readTemperature();
    if(isnan(t)){
      return -1; 
    }
  } 
  return t;
}
