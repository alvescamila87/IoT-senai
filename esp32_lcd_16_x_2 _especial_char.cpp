#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar[8] = {
  0b00000,
  0b11011,
  0b11011,
  0b00100,
  0b00100,
  0b10001,
  0b01110,
  0b00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

// Define os pinos de SDA e SCL
  Wire.begin(22, 23);
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.createChar(1, customChar);
  lcd.setCursor(0, 1); 
  lcd.write((byte)1);
  lcd.write((byte)1);
  lcd.write((byte)1);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100); // this speeds up the simulation
}
