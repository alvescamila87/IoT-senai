#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

// Define os pinos de SDA e SCL
  Wire.begin(22, 23);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0); //coluna 1, linha 0
  lcd.print("Hello world!");
  lcd.setCursor(0, 1); //coluna 0, linha 1
  lcd.print("ESP-DEVKIT I2C");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100); // this speeds up the simulation
}
