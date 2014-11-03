#ifndef _music_h_
#define _music_h_

#define NOTENAME_LENGTH 4
#define CHROMATIC_LENGTH 11 
#define CHROMATIC_INTERVALS {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

#include "Tones.h"

#ifndef _include_libs_arduino_
#define _include_libs_arduino_
#include <Arduino.h>
#endif;

class Scale {

  private:
  
  /* array of notes we can play - frequencies of the
     the chromatic scale from B0 (31 Hz) to D#8 (4978 Hz) */
  static uint32_t Notes[];
  
  /* length of the Notes array */
  static uint8_t Notes_length;
  
  /* array of note names for the notes we can play */
  static char NoteNames[][NOTENAME_LENGTH];
  
  /* root note of the scale
     position of the Notes array which is the
     root note of this scale */
  uint8_t root;

  /* interval composition of the scale
     1: half step    2: full step */
  uint8_t intervals[CHROMATIC_LENGTH];
  
  /* length of the intervals array
     how many intervals is the scale composed of */
  uint8_t intervals_length;
  
  /* note composition of the scale */
  /* max length of the scale is the length of the default chromatic scale */ 
  uint32_t notes[NOTE_COUNT];
  
  /* how many notes in the notes[] array of the scale */
  uint8_t notes_length;

  /* builds the note composition array for a scale object */
  void build_scale();
  
  /* prints to Serial debug information about this scale */
    
  public:
  Scale();
  Scale(uint8_t root_position, uint8_t intervals[], uint8_t length);

  void getNote(uint8_t positionInScale, int &frequency, char* &name);
  uint8_t getScaleLength();
  
  void print_debug();
};
  

#endif

