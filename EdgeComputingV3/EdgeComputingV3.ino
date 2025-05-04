#include <Wire.h>
#include "DHT.h"
#include <ESP32Servo.h>

#define DHTPIN      27
#define DHTTYPE     DHT11
#define BUZZER_PIN  14
#define RELAY_PIN   12
#define LDR_PIN     35
#define MQ2_PIN     32
#define MQ7_PIN     33
#define MQ135_PIN   34
#define LED_MERAH   4
#define LED_HIJAU   2
#define SERVO_PIN   13

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

// === FUNGSI DHT11, Relay, Buzzer, dan LED ===
void cekSuhuKelembapan() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("[DHT11] Gagal membaca data!");
    return;
  }

  Serial.print("[DHT11] Suhu: ");
  Serial.print(t);
  Serial.print("°C | Kelembapan: ");
  Serial.print(h);
  Serial.println("%");

  if (t > 32) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    Serial.println("[ALERT] Suhu tinggi! Kipas & Buzzer ON, LED Merah ON");
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    Serial.println("[INFO] Suhu normal. Kipas & Buzzer OFF, LED Hijau ON");
  }
}

// === FUNGSI LDR ===
void bacaLDR() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("[LDR] Nilai Cahaya: ");
  Serial.print(ldrValue);
  if (ldrValue < 1000) {
    Serial.println(" => Gelap");
  } else {
    Serial.println(" => Terang");
  }
}

// === FUNGSI MQ ===
void bacaMQ() {
  int mq2 = analogRead(MQ2_PIN);
  int mq7 = analogRead(MQ7_PIN);
  int mq135 = analogRead(MQ135_PIN);

  Serial.print("[MQ2] Gas Mudah Terbakar: ");
  Serial.println(mq2);

  Serial.print("[MQ7] CO (Karbon Monoksida): ");
  Serial.println(mq7);

  Serial.print("[MQ135] Kualitas Udara: ");
  Serial.println(mq135);
}

// === FUNGSI SERVO ===
void bukaTutupServo() {
  Serial.println("[SERVO] Buka Pakan (0°)");
  myServo.write(0);
  delay(2000);

  Serial.println("[SERVO] Tutup Pakan (90°)");
  myServo.write(90);
  delay(2000);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  myServo.attach(SERVO_PIN);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  Serial.println("=== Sistem Monitoring Siap ===");
}

void loop() {
  Serial.println("\n======= Pembacaan Sensor =======");

  cekSuhuKelembapan();
  bacaLDR();
  bacaMQ();
  bukaTutupServo();

  Serial.println("======= Akhir Pembacaan =======\n");
  delay(2000);
}
