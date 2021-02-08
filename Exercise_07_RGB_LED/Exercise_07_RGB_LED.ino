/*
 * Hibiscus Sense - Exercise 07 RGB LED
 * 
 * There is 1x RGB LED.
 * This RGB LED is connected to GPIO16 and integrated with WS2812.
 * WS2812 is an LED controller, which use single-wire control protocol to control the LEDs.
 * 
 * Therefore in the sketch,
 * we will use an Arduino library: Adafruit_NeoPixel from Adafruit.
 * 
 */
#include <Adafruit_NeoPixel.h>

// instance of the Adafruit_Neopixel class named as rgb.
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
