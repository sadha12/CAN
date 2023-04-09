#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Global variables for display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initDisplay() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to CAN");
  delay(1000);
  lcd.clear();
}

void displayInLED(uint8_t data) {
  lcd.setCursor(1, 0);
  lcd.print("CAN_Reciever ...");
  lcd.setCursor(2, 1);
  lcd.print("Pot_Value:");
  lcd.print(data);
  delay(500);
  lcd.clear();
}