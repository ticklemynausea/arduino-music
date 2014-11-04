#include "Song.h"

uint32_t current = 0;

void Song::loop_Play(Scale* s, Rhythm* r) {
 
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

    
    /* tempo */    
    int tempo = round(((knob_tempo) / (float)(ANALOG_MAX_VAL / ANALOG_FACTOR)) * BASE_TEMPO) + 200;

    uint32_t note = s->note_frequency(note_index);
    char* name = s->note_name(note_index);


    int duration = r->pattern[current];
    if (r->pattern[current] == 0) {
      if (r->pattern[current+1] == 0) {
        current = 0; deve
      }
    } else {
      uint32_t note_duration = tempo / duration;
      Song::note(note, note_duration);

      Serial.print("Playing " + String(name) + " for " + String(note_duration) + "ms\n");
  
      Display::Clear();
      Display::Text(0, 0, String(knob_range) + "r" + String(range) + " " + String(knob_position) + "p" + String(position) + " " + String(knob_tempo) + "t" + String(tempo));
      Display::Text(0, 4, name);
      Display::Text(0, 2, String());
      Display::Text(5, 4, String(note) + "Hz");
      Display::Text(13, 4, String(note_duration) + "ms");
      Display::Text(0, 1, "[" + String(random_lower) + "," + String(note_index) + "," + String(random_upper) + "]=" + String(delta));
    }

  current++;
}

void Song::note(uint32_t freq, uint32_t duration) {
  tone(SPEAKER_PWM, (unsigned int)note, (long unsigned int)duration);
  int pause = duration * 1.30;
  LED::Toggle();
  delay(pause);
  LED::Toggle();
  noTone(SPEAKER_PWM);  
}
