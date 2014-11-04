#ifndef _song_h_
#define _song_h_

#include "Scale.h"
#include "Rhythm.h"
#include "Display.h"
#include "LED.h"

/* * (+200) * */
#define BASE_TEMPO 1800

#define SPEAKER_PWM 2
#define ANALOG_RANGE 1
#define ANALOG_POSITION 2
#define ANALOG_TEMPO 3
#define ANALOG_MAX_VAL 1024
#define ANALOG_FACTOR 10


/* * checks if n is in the interval [a, b) * */
#define BETWEEN(n, a, b) ((n >= a) && (n < b))

class Song {
  public:
  static void loop_Play(Scale* s, Rhythm* r);
  static void note(uint32_t freq, uint32_t duration);
};

#endif
