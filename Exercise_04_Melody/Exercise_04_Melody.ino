/*
 * Hibiscus Sense - Exercise 04 Melody
 * 
 * There is 1x Small Buzzer on-board.
 * This is a passive buzzer and it is connected to GPIO13.
 * We need to generate Pulse Width Modulation (PWM) to control the vibration of the piezo element.
 * 
 * In Arduino ESP32 programming there is no analogWrite() function as usual.
 * ESP32 has 16 channel, from 0 - 15. Channel does not mean GPIO number!
 * Therefore in the sketch,
 * we will use ledcAttachPin(), ledcDetachPin() and ledcWriteTone() function,
 * to generate the PWM signal on GPIO13.
 * 
 */

// include the preset tones file, which included in local header files named tones.h
#include "tones.h"

void setup() {
  
}

void loop() {
  // ledcAttachPin() function to declare GPIO and PWM channels.
  // 1st argument: GPIO number.
  // 2nd argument: PWM channel number.
  ledcAttachPin(13, 0);
  // ledcWriteTone() function will generate PWM signal based on given tone frequency.
  // 1st argument: PWM channel number.
  // 2nd argument: Tone frequency.
  ledcWriteTone(0, NOTE_D4);  // buzzer will sound according to NOTE_D4.
  delay(500);

  // ledcDetachPin() function to declare GPIO and PWM channels.
  ledcWrite(0, 0);  // buzzer has no sound since PWM signal is 0.
  delay(500);
}
