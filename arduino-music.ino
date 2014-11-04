/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
#include "Scale.h"
#include "Rhythm.h"
#include "Song.h"

#ifndef _include_libs_i2clcd_
#define _include_libs_i2clcd_
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#endif;

#define ANALOG_OPEN 0


Scale *s;
Rhythm *r;

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(ANALOG_OPEN));

  LED::Initialize();
  
  Display::Initialize();

  uint8_t major[] = {2, 2, 1, 2, 2, 2, 1};
  
  Serial.print("Initializing scale... ");
  s = new Scale(0, major, 7);
  Serial.print("done.\n");  
  
  Serial.print("Initializing rhythm... ");
  r = new Rhythm(4, 4, 100);
  Serial.print("done.\n");  
  
  s->print_debug();
  
  r->print_debug();
}


void loop() {

  Song::loop_Play(s, r);

}


