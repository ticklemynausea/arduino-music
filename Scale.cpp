#include "Scale.h"
#include "Tones.h"

#include <assert.h>

/*
 * Data
 */
uint32_t Scale::Notes[] = {
 NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1,
 NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2,
 NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3, NOTE_CS3,
 NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3,
 NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4,
 NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5,
 NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_CS6,
 NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6,
 NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7,
 NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8
};

//uint8_t Scale::Notes_length = sizeof(Scale::Notes) / sizeof(uint32_t);
uint8_t Scale::Notes_length = NOTE_COUNT;

char Scale::NoteNames[][NOTENAME_LENGTH] = {
 "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1",
 "G#1", "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2",
 "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2", "C3", "C#3",
 "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3",
 "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4",
 "G#4", "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5",
 "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5", "C6", "C#6",
 "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6",
 "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7",
 "G#7", "A7", "A#7", "B7", "C8", "C#8", "D8", "D#8"
};


/* default: chromatic scale */
Scale::Scale() {

  /* chromatic intervals */
  this->intervals_length = CHROMATIC_LENGTH;
  
  /* default scale start is the first note in Notes */
  this->root = 0;
  
  /* default is to initialize the intervals array with the chromatic scale intervals */
  uint8_t chromatic[] = CHROMATIC_INTERVALS;
  memcpy(this->intervals, chromatic, this->intervals_length);
  
  /* build scale array */
  this->build_scale();
}

Scale::Scale(uint8_t root, uint8_t intervals[], uint8_t intervals_length) {
  this->intervals_length = intervals_length;
  this->root = root;
  memcpy(this->intervals, intervals, this->intervals_length);
  
  /* build scale array */
  this->build_scale();
}

void Scale::build_scale() {
  
  /* pick which notes belong to the desired scale from the static Notes array
     and place them in the notes array. place the total amount of such notes in
     the notes_length array */

  //Serial.print("building scale\n");
  uint8_t Notes_position = 0;
  uint8_t notes_position = 0;
  while (Notes_position < NOTE_COUNT) {
    //Serial.print("" + String(Notes_position) + "," + String(notes_position) + "\n");;
    this->notes[notes_position] = Notes_position;
    
    notes_position++;
    Notes_position += this->intervals[notes_position % intervals_length];
  }
  this->notes_length = notes_position - 1;
  //Serial.print("Scale built\n");
}

uint8_t Scale::length() {
  return this->notes_length;
}

uint32_t Scale::note_frequency(uint8_t position) {
  return Scale::Notes[this->notes[position]];
}

char * Scale::note_name(uint8_t position) {
  return Scale::NoteNames[this->notes[position]];
}

void Scale::print_debug() {
  Serial.print(
    "Hi. s->intervals:" + String(this->intervals_length) + "\t[");
    
  for (uint8_t i = 0; i < this->intervals_length; i++) 
    Serial.print(String(this->intervals[i]) + ",");

  Serial.print(
    "]\tnotes:" + String(this->notes_length) + "\t[");
    
  for (uint8_t i = 0; i < this->notes_length; i++) 
    Serial.print(String(this->notes[i]) + ",");
    
  Serial.print(
    "] notes_length:" + String(this->notes_length) + "\t" +
    "\n");
}

