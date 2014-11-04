#include "Rhythm.h"

/*
 Data
*/

uint8_t Rhythm::Patterns[][PATTERN_MAX_LENGTH] = {
  {1, 0},
  {2, 2, 0},
  {4, 4, 4, 4, 0},
  {8, 8, 8, 8, 8, 8, 8, 8, 0}
};

uint8_t Rhythm::Patterns_length = 4;

Rhythm::Rhythm(uint8_t measure_number_beats, uint8_t measure_beat_value) {
  this->measure_number_beats = measure_number_beats;
  this->measure_beat_value = measure_beat_value;
  this->pattern_length = RHYTHM_PATTERN_LENGTH;
  
  this->build_rhythm();
}

Rhythm::Rhythm(uint8_t measure_number_beats, uint8_t measure_beat_value, uint32_t measures_count) {
  this->measure_number_beats = measure_number_beats;
  this->measure_beat_value = measure_beat_value;
  this->measures_count = measures_count;
  this->build_rhythm();  
}

void Rhythm::build_rhythm() {
    
  /* total number of notes copied */
  uint32_t notes_copied = 0;

  for (uint32_t i = 0; i < RHYTHM_PATTERN_LENGTH; i++) {

    /* pick a random rhythmic pattern from the list */
    uint8_t Patterns_i = random(Rhythm::Patterns_length);
    
    /* aux counter to copy from one array to the other */
    uint8_t j = 0;
    
    /* total number of measures copied */
    uint8_t measures_copied = 0;
    
    while (Rhythm::Patterns[Patterns_i][j] != 0) {
      this->pattern[i+j] =  Rhythm::Patterns[Patterns_i][j];
      notes_copied++;
      j++;
    }
    i += j;
    
    this->pattern[i] = 0;
    
    measures_copied++;
    if (measures_copied >= this->measures_count) {
      this->pattern[++i] = 0;
    }
  }
  
  this->pattern_length = notes_copied;

}

void Rhythm::print_debug() {
  Serial.print(
    "Hi. r->pattern:" + String(this->pattern_length) + "\t [");
  
  for (uint8_t i = 0; i < this->pattern_length; i++) {
    if (this->pattern[i] == 0) {
      Serial.print(String("]["));
    } else {
      Serial.print(String(this->pattern[i]) + ",");
    }
  }

  Serial.print(
    "]\n");  
}

