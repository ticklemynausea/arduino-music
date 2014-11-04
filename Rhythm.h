#ifndef _rhythm_h_
#define _rhythm_h_

#define RHYTHM_PATTERN_LENGTH 512
#define PATTERN_MAX_LENGTH 16

/* Minimum note: sixteenth note */
#define NOTE_VALUE_MIN 16

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#endif;

class Rhythm {

  private:
  /* length of the Notes array */
  static uint8_t Patterns_length;
  
  /* array of note names for the notes we can play */
  static uint8_t Patterns[][PATTERN_MAX_LENGTH];

  public:

  /* Time Signature: number of beats in each measure */
  uint8_t measure_number_beats;
  
  /* Time Signature: value of each beat in the measure */
  uint8_t measure_beat_value;
  /* note composition of the rhythmic pattern - adjusted for measure_number_beats
     and measure_beat_value.
     positive numbers are notes, negative numbers are pauses, zero marks measure end */
  int8_t pattern[RHYTHM_PATTERN_LENGTH];

  /* length of the rhythmic pattern */
  uint32_t pattern_length;

  /* measure count of the rhythmic pattern */
  uint8_t measures_count;
  
  void build_rhythm();

  Rhythm(uint8_t measure_number_beats, uint8_t measure_beat_value);
  Rhythm(uint8_t measure_number_beats, uint8_t measure_beat_value, uint32_t measures_count);
  void print_debug();

};

#endif;
