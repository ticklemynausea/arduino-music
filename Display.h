#ifndef _lcd_h_
#define _lcd_h_

#include <LiquidCrystal_I2C.h>

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#endif

class Display {

  private:
  static LiquidCrystal_I2C lcd;
  
  public:
  static void Initialize();
  static void Text(uint8_t column, uint8_t row, String text);
  static void Clear();

};

#endif
