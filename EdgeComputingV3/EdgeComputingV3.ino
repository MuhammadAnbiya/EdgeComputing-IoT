#include <Wire.h>
//#include <BH1750.h>

#define BUZZER_PIN 14

//BH1750 lightMeter;

void setup(){
  Serial.begin(9600);
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
  
  //  delay(2000);

 }
