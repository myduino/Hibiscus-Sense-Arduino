void setup() {
  // configure PWM controller congfiguration
  ledcSetup(0, 5000, 8);
  // declare the GPIO number for PWM signal output
  ledcAttachPin(2, 0);
}

void loop() {
  // function for() to create decremental value by 1 start from 255 --> 0
  for(int brightness = 255; brightness >= 0; brightness--){   
    // generate PWM output signal according to variable brightness value
    ledcWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again
  delay(200);
}
