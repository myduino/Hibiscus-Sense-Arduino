/*
 * Hibiscus Sense - Exercise 03 Breathing Light
 * 
 * There is 1x blue LED.
 * This LED is connected to GPIO2 of ESP32 microcontroller.
 * We need to generate PWM output signal on GPIO2 to control the brightness of this LED.
 * 
 * Therefore in the sketch,
 * we configure the PWM controller, choose GPIO for PWM signal output 
 * and generate the PWM signal on chosen GPIO.
 * 
 */

void setup() {
  // declare the GPIO number for PWM signal output
  pinMode(2, OUTPUT);
}

void loop() {
  // statement for() to create decremental value by -1
  // for active-low LED circuit, the PWM value begin from 255 --> 0
  // from OFF LED to linear increasing brightnes.
  for(int brightness = 255; brightness >= 100; brightness--){   
    analogWrite(2, brightness);
    delay(15);
  }
  // wait for 0.2 seconds
  delay(200);
  
  // statement for() to create incremental value by +1
  // for active-low LED circuit, the PWM value begin from 255 --> 0
  // from ON LED to linear decreasing brightnes.
  for(int brightness = 100; brightness <= 255; brightness++){
    analogWrite(2, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again
  delay(200);
}
