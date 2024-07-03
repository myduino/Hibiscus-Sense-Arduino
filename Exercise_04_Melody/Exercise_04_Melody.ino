/*
 * Hibiscus Sense - Exercise 04 Melody
 * 
 * There is 1x Small Buzzer on-board.
 * This is a passive buzzer and it is connected to GPIO13.
 * We need to generate Pulse Width Modulation (PWM) to control the vibration of the piezo element.
 * 
 * We will use tone(), and noTone() function,
 * tone() function is used to generates a square wave of the specified frequency (and 50% duty cycle) on a GPIO pin.
 * 
 */

// include the preset tones file, which included in local header files named tones.h
#include "tones.h"

void setup() {
  
}

void loop() {
  // tone() function will generate PWM signal based on given tone frequency.
  // 1st argument: GPIO number.
  // 2nd argument: Tone frequency.
  tone(13, NOTE_D4);  // buzzer will sound according to NOTE_D4.
  delay(500);

  noTone(13);  // buzzer has no sound since PWM signal is 0.
  delay(500);
}
