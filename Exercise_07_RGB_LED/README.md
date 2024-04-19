# Exercise 07: RGB LED

The aim of this exercise is to control the WS2812 RGB LED (connected to GPIO16) by animating the LED with different colors or patterns.

RGB LED is a tri-color LED in a package:
- **Red**
- **Green**
- **Blue**

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven.png" width="400"></a></p>

An RGB LED, have four leads, for each colour and one common anode (+ve) or common cathode (-ve). In `common cathode` RGB LED, three LEDs share one `(-ve) connection`, while, in `common anode` RGB LED, three LEDs share one `(+ve) connection`. The image above, shows that the RGB LED is common cathode, as the longest lead is (-ve) lead. We can use ESP32's PWM controller to control each RGB LED lead to produce different colour.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven-a.png" width="400"></a></p>

There is 1x RGB LED on Hibiscus Sense labelled as **`WS2812`** and it is a special RGB LED. WS2812 is an addressable RGB LED that can be connected in series. We can control the colour of the RGB LED colour in its position, with just only one pin to ESP32 microcontroller, amazing!

WS2812 have 4 connector:
1. **`VDD`** - Power supply 3.5~5.3V. 3.3V also enough to power the RGB LED.
2. **`DOUT`** - Control data signal output.
3. **`VSS`** - GND terminal.
4. **`DIN`** - Control data signal input.

The schematic of WS2812 RGB on Hibiscus Sense, as in the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-seven.png" width="500"></a></p>

To control usual RGB LED, we can generate the PWM signal output to its indivial lead to produce different colour of RGB LED. Since, our RGB LED on Hibiscus Sense is WS2812, we need to use [Adafruit_Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) library to control the colour of RGB LED using single-wire connection. Prior to program the ESP32, we need to install the library from Arduino IDE's Library Manager, as on the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven-b.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch as below:

## Complete Sketch
```cpp
#include <Adafruit_NeoPixel.h>

// instance of the Adafruit_Neopixel class as rgb.
// 1st argument: number of LED, Hibiscus Sense has 1x RGB LED.
// 2nd argument: the RGB LED connected to which pin? Answer: GPIO16 of ESP32.
Adafruit_NeoPixel rgb(1, 16); 

void setup() {
  // Initialize the library with begin() function
  // to prepare the output
  rgb.begin();
  
  // The show() function will push the data to control the RGB LED,
  // since there are no colors has been set yet,
  // this function will send 'OFF' data as the RGB LED will turn OFF.
  // Therefore this function is not necessary, but it is here to turn OFF the RGB LED,
  // if there is any prior colors lighting ON.
  rgb.show();

}

void loop() {
  // setPixelColor() function for setting the LED data, which according to
  // the LED position and the RGB color which range from 0 to 255.
  // 1st argument: the position of the LED, since we have 1x LED, the 1st position is 0.
  // 2nd argument: the Red color value.
  // 3nd argument: the Green color value.
  // 4nd argument: the Blue color value.
  rgb.setPixelColor(0, 255, 0, 255);  // combination of Red and Blue color = magenta

  // calling show() function to push the data to the LED.
  rgb.show();

}
```

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. By observation, the colour output from RGB LED is magenta.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven-c.jpg" width="500"></a></p>

## Detail Sketch Explanations

Include `Adafruit_Neopixel` library's header file and declare an instance named `rgb` for `Adafruit_NeoPixel` class and both of its argument, the number of the RGB LED: `1` and connected to which GPIO pin: `16`.
```cpp
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel rgb(1, 16); 
```

Initialize `Adafruit_Neopixel` library with `begin()` function.
```cpp
rgb.begin();
```

If `show()` function we execute without any colour set, it will send `OFF` command to the RGB LED. We call this function after initialization, because we just want to make sure any previous colour program back to OFF during first start.
```cpp
rgb.show();
```

`setPixelColor()` function is to set the position of the LED and the colour output of the RGB LED. The combination of the RGB colour range from 0-255 as on the image below, for example in the line of sketch below, RED: 255, GREEN: 0 and BLUE: 255, represent magenta.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven-d.gif" width="600"></a></p>

```cpp
rgb.setPixelColor(0, 255, 0, 255);
rgb.show();
```

## Further Experiment

You can create custom color patterns and explore animations like color fading, rainbow effects, or chasing patterns.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>