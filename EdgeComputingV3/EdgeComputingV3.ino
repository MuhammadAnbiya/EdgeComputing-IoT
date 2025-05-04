#include <Wire.h>
//#include <BH1750.h>
#include "DHT.h"


#define DHTPIN 27         
#define DHTTYPE DHT11 
#define BUZZER_PIN 14


//BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);


void setup(){
  Serial.begin(9600);
  dht.begin();
//  Wire.begin(21, 22);

//  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)){
//    Serial.println("Sensor Siap...");
//  } else{
//    Serial.println("Sensor Gagal");
//    while(1);
//  }
}

void loop() {
  //  float lux = lightMeter.readLightLevel();
  //  Serial.print("Intensitas Cahaya: ");
  //  Serial.print(lux);
  //  Serial.println(" Lux");

  tone(BUZZER_PIN, 1000);
  delay(1000);
  noTone(BUZZER_PIN);
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT22!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(t);
    Serial.print("°C  |  Kelembapan: ");
    Serial.print(h);
    Serial.println("%");
  }
  
  delay(2000);

 }
