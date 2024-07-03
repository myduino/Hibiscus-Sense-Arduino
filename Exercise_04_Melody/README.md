# Exercise 04: Control Small Buzzer on GPIO13

The aim of this exercise is to create a simple melody like alarm beeping sound by playing specific frequencies in sequence on the Hibiscus Sense board’s small buzzer (connected to GPIO13).

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-four-b.png" width="400"></a></p>

On Hibiscus Sense, there is 1x small buzzer, labelled as `BUZZER` on-board, as circled on the image above.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-four.png" width="300"></a></p>

Buzzer is a piezoelectrical electronic components, which generate tones when the piezo elements is vibrated based on given voltage supply, different voltage will produce different vibration, thus generating different tone. Since ESP32 has the ability to generate range of voltage using, the built-in PWM controllers, we can apply it on our small buzzer to generate tone.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-four-a.gif" width="400"></a></p>

The operating voltage of the small buzzer on the Hibiscus Sense is ranging from 2-4V with rated voltage of 3V, the `(+ve) terminal` of the buzzer is connected to `GPIO13`, while the `(-ve) terminal` is connected to `GND`, as shown in the schematic below. The 3rd terminal of the buzzer is not connected.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/schematic-exercise-four.png" width="400"></a></p>

To produce the tone or melody from the buzzer, we can use `tone(_gpio_, _frequency_)` function to control the output frequency on GPIO13. While, we can use `noTone(_gpio_)` function to stop generating the frequency.

In this exercise, all the available note and its frequency to produce the tone, has been declared on a header file, titled `tones.h` as [here](https://github.com/myduino/Hibiscus-Sense-Arduino/blob/main/Exercise_04_Melody/tones.h) for available tones.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-four-c.png" width="500"></a></p>

Since we have notice, we need to use `ledcWriteTone()` function instead of `ledcWrite()` function to generate the PWM output signal for the buzzer to produce the tone, let's write the program as below:

## Complete Sketch
```cpp
// include the preset tones file, which included in local header files named tones.h
#include "tones.h"

void setup() {
  // configure PWM controller congfiguration
  ledcSetup(0, 5000, 8);
  // declare the GPIO number for PWM signal output
  ledcAttachPin(13, 0);
}

void loop() {
  // ledcWriteTone() function will generate PWM signal based on given tone frequency.
  // 1st argument: PWM channel number.
  // 2nd argument: Tone frequency.
  ledcWriteTone(0, NOTE_D4);  // buzzer will sound according to NOTE_D4.
  delay(500);

  ledcWrite(0, 0);  // buzzer has no sound since PWM signal is 0.
  delay(500);
}
```
You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. Once sucessfully uploaded the program, you'll hear the beeping sound.

## Detail Sketch Explanations

First, we need to include header file, which has the declaration of all available note.
```cpp
#include "tones.h"
```

In `void setup()` function, we have to configure the PWM channel using `ledcSetup()` function and declare buzzer (+ve) terminal attach to GPIO13 using `ledcAttachPin()` function.
```cpp
ledcSetup(0, 5000, 8);
ledcAttachPin(13, 0);
```

Inside the `void loop()` function, we use `ledcWriteTone()` function to generate sound of `NOTE_D4` frequency, while `ledcWrite()` function to turn OFF the buzzer. Therefore, the execution of these functions repeatedly, producing alarm-like sound.
```cpp
ledcWriteTone(0, NOTE_D4);  // buzzer will sound according to NOTE_D4.
delay(500);

ledcWrite(0, 0);  // buzzer has no sound since PWM signal is 0.
delay(500);
```
## Further Experiment
You can modify the melody by changing the frequency values or you can upload the sketch below play melodies.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>