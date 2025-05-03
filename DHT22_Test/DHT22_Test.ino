#include "DHT.h"

#define DHTPIN 2        // Pin data DHT22
#define DHTTYPE DHT22   // Tipe sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Mulai membaca sensor DHT22...");
  dht.begin();
}

void loop() {
  delay(2000);  // Baca setiap 2 detik

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT22!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("°C  |  Kelembapan: ");
  Serial.print(h);
  Serial.println("%");
}
