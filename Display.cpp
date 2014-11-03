#include "Display.h"

// Set the LCD I2C address: 0x27
LiquidCrystal_I2C Display::lcd = LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void Display::Initialize() {
  Display::lcd.begin(20, 4);

  for(int i = 0; i< 3; i++) {
    Display::lcd.backlight();
    delay(100);
    Display::lcd.noBacklight();
    delay(100);
  }
  Display::lcd.backlight(); // finish with backlight on  
}

void Display::Clear() {
  Display::lcd.clear();
}

void Display::Text(uint8_t column, uint8_t row, String text) {
  Display::lcd.setCursor(column, row); //Start at character 0 on line 0
  Display::lcd.print(text); 
}
