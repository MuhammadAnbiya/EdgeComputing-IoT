#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat, kolom, baris

void setup() {
  Wire.begin(18, 19); // Pin SDA, SCL khusus ESP32
  lcd.begin(16, 2);   // Harus isi kolom & baris
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello ESP32!");
  lcd.setCursor(0, 1);
  lcd.print("LCD OK");
}

void loop() {
  lcd.print("temaku semua pada jahat tantee");
}
