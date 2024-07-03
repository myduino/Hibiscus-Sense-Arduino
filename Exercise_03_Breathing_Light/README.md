# Exercise 03: Control Blue LED on GPIO2 (Breathing Light Effect)

The aim of this exercise is to control the blue LED on GPIO2, gradually changing the LED brightness in a smooth, rhythmic pattern to simulate breathing light effect on the Hibiscus Sense board.

This exercise is a continuation from [Exercise 2](https://github.com/myduino/Hibiscus-Sense-Arduino#exercise-2-control-blue-led-on-gpio2-glowing-light-effect).

In Exercise 2, we use `for()` statement to automatically generate decremental PWM value from 255-150 for the `(active-low circuit)` to produce an output of glowing light effect, while in this exercise we produce breathing light effect.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-three.gif" width="500"></a></p>

It's easy ... we just need to add another `for()` statement to automatically generate decremental PWM value from 255-100 (lights up) and incremental PWM value from 100-255 (fades off). The complete sketch as follows:

## Complete Sketch
```cpp
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
```

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. By observation, the output of the blue LED is repeated breathing light effect, which the results from decremental and incremental value of the PWM signal output.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-three-a.gif" width="600"></a></p>

## Further Experiment
You can adjust the rate of brightness change to customize the breathing speed.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>