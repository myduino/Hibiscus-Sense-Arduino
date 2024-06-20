/*
 * Hibiscus Sense - Exercise 02 Glowing Light
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
  // declare the GPIO number for PWM signal output.
  pinMode(2, OUTPUT);
}

void loop() {
  // statement for() to create decremental value by -1, start from 255 --> 0
  // from OFF LED to linear increasing brightness, for active-low circuit.
  for(int brightness = 255; brightness >= 0; brightness--){   
    // function will generate PWM output signal according to variable brightness value
    analogWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again.
  delay(200);
}
