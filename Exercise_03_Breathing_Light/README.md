This exercise is a continuation from [Exercise 2](https://github.com/myinvent/hibiscus-sense-arduino#exercise-2-control-blue-led-on-gpio2-glowing-light-effect).

In Exercise 2, we use `for()` function to automatically generate decremental PWM value from 255-0 for the `(active-low circuit)` to produce an output of glowing light effect, while in this exercise we produce breathing light effect.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-three.gif" width="500"></a></p>

It's easy ... we just need to add another `for()` function to automatically generate incremental PWM value from 0-255, so the program as follows:

**Complete Sketch**
```cpp
void setup() {
  // configure PWM controller congfiguration
  ledcSetup(0, 5000, 8);
  // declare the GPIO number for PWM signal output
  ledcAttachPin(2, 0);
}

void loop() {
  // function for() to create decremental value by 1 start from 255 --> 0
  // from OFF LED to linear increasing brightness, for active-low circuit
  for(int brightness = 255; brightness >= 0; brightness--){   
    ledcWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again
  delay(200);
  
  // function for() to create incremental value by 1 start from 0 --> 255
  // from ON LED to linear decreasing brightness, for active-low circuit
  for(int brightness = 0; brightness <= 255; brightness++){   
    ledcWrite(0, brightness);
    delay(15);
  }

  delay(200);
}
```

Now, we can upload the complete sketch to ESP32, then observe the output. By observation, the output of the blue LED is repeated breathing light effect, which the results from decremental and incremental value of the PWM signal output.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-three-a.gif" width="600"></a></p>

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>