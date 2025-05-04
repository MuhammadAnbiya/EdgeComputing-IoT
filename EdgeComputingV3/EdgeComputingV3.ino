#include <Wire.h>
#include "DHT.h"

#define DHTPIN 27
#define DHTTYPE DHT11
#define BUZZER_PIN 14
#define RELAY_PIN 12
#define LDR_PIN 35
#define MQ2_PIN   32
#define MQ7_PIN   33
#define MQ135_PIN 34

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  noTone(BUZZER_PIN);           
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int smokeGas = analogRead(MQ2_PIN);
  int carbonMonoxide = analogRead(MQ7_PIN);
  int airQuality = analogRead(MQ135_PIN);

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT11!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("°C  |  Kelembapan: ");
  Serial.print(h);
  Serial.println("%");

  if (t > 32) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("PERINGATAN: Suhu tinggi! Buzzer & Kipas ON");
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Suhu normal. Buzzer & Kipas OFF");
  }

  int ldrValue = analogRead(LDR_PIN);
  Serial.print("Nilai LDR (Cahaya): ");
  Serial.println(ldrValue);

  if (ldrValue < 1000) {
    Serial.println("Keadaan: Gelap");
  } else {
    Serial.println("Keadaan: Terang");
  }


  Serial.print("Asap & Gas Mudah Terbakar (MQ-2): ");
  Serial.print(smokeGas);
  Serial.print(" | CO (MQ-7): ");
  Serial.print(carbonMonoxide);
  Serial.print(" | Kualitas Udara (MQ-135): ");
  Serial.println(airQuality);
  Serial.println("------------------------");
  
  delay(2000);
}
