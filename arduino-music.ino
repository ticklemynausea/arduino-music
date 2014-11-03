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
#include "LED.h"
#include "Display.h"

#ifndef _include_libs_i2clcd_
#define _include_libs_i2clcd_
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#endif;

#define SPEAKER_PWM 2
#define ANALOG_OPEN 0
#define ANALOG_RANGE 1
#define ANALOG_POSITION 2
#define ANALOG_TEMPO 3
#define ANALOG_MAX_VAL 1024
#define ANALOG_FACTOR 10

/* * checks if n is in the interval [a, b) * */
#define BETWEEN(n, a, b) ((n >= a) && (n < b))

/* * (+200) * */
#define BASE_TEMPO 1800




// note durations: 4 = quarter note, 8 = eighth note, etc.:
int durations[] = {
  4, 8, 8
};

int num_durations = 3;

Scale *s;

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(ANALOG_OPEN));

  LED::Initialize();
  
  Display::Initialize();

  uint8_t major[] = {2, 2, 1, 2, 2, 2, 1};
  s = new Scale(0, major, 7);

  s->print_debug();
}


void loop() {

    /* analog read */
    int knob_range = analogRead(ANALOG_RANGE) / ANALOG_FACTOR;
    int knob_position = analogRead(ANALOG_POSITION) / ANALOG_FACTOR;
    int knob_tempo = analogRead(ANALOG_TEMPO) / ANALOG_FACTOR;
    
    /* calculate range and position */
    int range = round((knob_range * s->length()) / (float)(ANALOG_MAX_VAL / ANALOG_FACTOR));
    int position =  round((knob_position * s->length()) / (float)(ANALOG_MAX_VAL / ANALOG_FACTOR));
    
    
    /* array sizes */
    int random_lower = position - (range / 2);
    random_lower = BETWEEN(random_lower, 0, s->length() - 1) ? random_lower : 0;

    int random_upper = position + (range / 2);
    random_upper = BETWEEN(random_upper, 0, s->length() - 1) ? random_upper : s->length();
    
    int delta = random_upper - random_lower;
    int note_index = random(random_lower, random_upper);
    //Serial.print(note_index);
    /* get note duration */
    int duration_index = random(num_durations);
    
    /* tempo */    
    int tempo = round(((knob_tempo) / (float)(ANALOG_MAX_VAL / ANALOG_FACTOR)) * BASE_TEMPO) + 200;

    int note = s->note_frequency(note_index);
    char* name = s->note_name(note_index);

    int duration = durations[duration_index];
    
    int note_duration = tempo / duration;

    tone(SPEAKER_PWM, note, note_duration);

    char* name = s->note_name(note_index);

    Display::Clear();
    Display::Text(0, 0, String(knob_range) + "r" + String(range) + " " + String(knob_position) + "p" + String(position) + " " + String(knob_tempo) + "t" + String(tempo));
    Display::Text(0, 4, name);
    Display::Text(0, 2, String());
    Display::Text(5, 4, String(note) + "Hz");
    Display::Text(13, 4, String(note_duration) + "ms");
    Display::Text(0, 1, "[" + String(random_lower) + "," + String(note_index) + "," + String(random_upper) + "]=" + String(delta));

    //Serial.println(s);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pause = note_duration * 1.30;
    LED::Toggle();
    delay(pause);
    LED::Toggle();
    noTone(SPEAKER_PWM);
}


