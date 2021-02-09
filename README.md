# Hibiscus Sense ESP32 Arduino Tutorial

<p align="right">
  <a href="https://myduino.com/product/myd-036/"><img src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fmyinvent%2Fhibiscus-sense-arduino&count_bg=%2379C83D&title_bg=%23555555&icon=powerbi.svg&icon_color=%23E7E7E7&title=hits&edge_flat=false"/></a>
</p>

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-logo.png" width="300"></a></p>
<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense.png" width="400"></a></p>

> Whenever you are thinking of quick Internet of Things (IoT) hardware prototyping / development, just grab [**Hibiscus Sense**](https://myduino.com/product/myd-036/) and focus on programming :sunglasses:

## Table of Content
- [Introduction](https://github.com/myinvent/hibiscus-sense-arduino#introduction)
- [Hibiscus Sense Features](https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-features)
- [Hibiscus Sense Pinout Diagram](https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-pinout-diagram)
- [Learning Material Preparation](https://github.com/myinvent/hibiscus-sense-arduino#learning-material-preparation)
- [Interfacing Hibiscus to Computer's USB Port](https://github.com/myinvent/hibiscus-sense-arduino#interfacing-hibiscus-to-computers-usb-port)
- [Exercise 1: Control Blue LED on GPIO2 (Strobe Light Effect)](https://github.com/myinvent/hibiscus-sense-arduino#exercise-1-control-blue-led-on-gpio2-strobe-light-effect)
- [Exercise 2: Control Blue LED on GPIO2 (Glowing Light Effect))](https://github.com/myinvent/hibiscus-sense-arduino#exercise-2-control-blue-led-on-gpio2-glowing-light-effect)
- [Exercise 3: Control Blue LED on GPIO2 (Breathing Light Effect)](https://github.com/myinvent/hibiscus-sense-arduino#exercise-3-control-blue-led-on-gpio2-breathing-light-effect)
- [Exercise 4: Control Small Buzzer on GPIO13](https://github.com/myinvent/hibiscus-sense-arduino#exercise-4-control-small-buzzer-on-gpio13-melody)
- [Exercise 5: Serial Communication (Hibiscus Sense & Computer)](https://github.com/myinvent/hibiscus-sense-arduino#exercise-4-serial-communication-hibiscus-sense--computer)
- [Exercise 6: Monitor Pushbutton Status on GPIP0 (LED ON/OFF)](https://github.com/myinvent/hibiscus-sense-arduino#exercise-6-monitor-pushbutton-status-on-gpip0-led-onoff)
- [Exercise 7: Control RGB LED on GPIO16](https://github.com/myinvent/hibiscus-sense-arduino#exercise-7-control-rgb-led-on-gpio16)
- [Exercise 8: Monitor Proximity Value from APDS9960](https://github.com/myinvent/hibiscus-sense-arduino#exercise-8-monitor-proximity-value-from-apds9960)
- [Exercise 9: Monitor Gesture Direction using APDS9960](https://github.com/myinvent/hibiscus-sense-arduino#exercise-9-monitor-gesture-direction-from-apds9960)
- [Exercise 10: Monitor Environmental Value using BME280](https://github.com/myinvent/hibiscus-sense-arduino#exercise-10-monitor-environmental-value-using-bme280)
- [Exercise 11: Monitor 6-axis Motion Tracking using MPU6050](https://github.com/myinvent/hibiscus-sense-arduino#exercise-11-monitor-6-axis-motion-tracking-using-mpu6050)

## Introduction

[Hibiscus Sense](https://myduino.com/product/myd-036/) is a rapid Internet of Things (IoT) development board, powered by the mighty and popular dual-core [ESP32](https://www.espressif.com/en/products/socs/esp32) microcontroller, which on-board equipped with rich profusion sensor's data and basic actuators as below:
- 3 sensors:
  - **APDS9960**: an environment sensor, which sense *proximity, RGB* and *gesture*.
  - **BME280**: an environment sensor, which sense the *altitude, barometric pressure, humidity* and *temperature*.
  - **MPU6050**: 6-axis motion tracking sensor, which sense *3-axis gravitational acceleration, 3-axis rotational velocity* and *temperature*.
- 3 actuators:
  - **Buzzer**: short distance small buzzer.
  - **LED**: blue LED.
  - **RGB LED**: WS2812 RGB LED.

Hibiscus Sense comes with **USB Type-C** to power up the board and to program the ESP32. The on-board USB-to-Serial converter **Silicon Labs CP2104** with **automatic bootloader reset** circuit, we don’t have to press the RESET button each time to upload the program.

Although, we can program ESP32 using other programming language such as C, C++ and Micropython, but in this tutorial we will be using [Arduino](https://www.arduino.cc/) as the learning and prototyping platform.

## Hibiscus Sense Features

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-features.png" width="900"></a></p>

## Hibiscus Sense Pinout Diagram

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-pinout.png" width="900"></a></p>

- **Blue LED** is connected to ESP32's `GPIO2`.
- **Small Buzzer** is connected to ESP32's `GPIO13`.
- **WS2812 RGB LED** is connected to ESP32's `GPIO16`.
- All GPIO can generate digital input/output (3.3V) and PWM signal output, except `GPIO34-GPIO39` because it is an input pin only.
- ESP32's `VSPI` is complete **MISO** `GPIO19`, **MOSI** `GPIO32`, **CLK** `GPIO18` and **CS** `GPIO5`.
- ESP32's `I2C` **SDA** `GPIO21` and **SCL** `GPIO22`, without pullup resistor.
- **Sensors**: **APDS9960**, **BME280** and **MPU6050** interfaced to the ESP32's `I2C`, respective I2C address: `0x39`, `0x77` and `0x68`.
- Avoid using `ADC2` channel while using WiFi.
- Each GPIO absolute maximum current drawn only 16mA.
- Board measurement including header in mm: 58.7 x 27 x 13.3 (length x width x height).
- Package measurement in mm: 71.8 x 35.5 x 20.4 (length x width x height).



## Learning Material Preparation

Prior to start learning to control the actuators and acquire data from the sensors on Hibiscus Sense using Arduino programming tool and language, we have to make sure all learning material is ready, as below:
1. Hibiscus Sense and a USB cable Type-A to Type-C. If you don't own it yet, you are always welcome to purchase it from :shopping_cart: [Myduino](https://myduino.com/product/myd-036/)
2. Arduino IDE. Download it from here: [Windows](https://downloads.arduino.cc/arduino-1.8.13-windows.exe) / Linux [32-bit](https://downloads.arduino.cc/arduino-1.8.13-linux32.tar.xz), [64-bit](https://downloads.arduino.cc/arduino-1.8.13-linux64.tar.xz), [ARM 32-bits](https://downloads.arduino.cc/arduino-1.8.13-linuxarm.tar.xz) [ARM 64-bits](https://downloads.arduino.cc/arduino-1.8.13-linuxaarch64.tar.xz) / [Mac OSX](https://downloads.arduino.cc/arduino-1.8.13-macosx.zip).
3. [ESP32](https://github.com/espressif/arduino-esp32) hardware library. Below is screenshot, showing the `Arduino IDE Boards Manager` (Arduino IDE Menu: **_Tools > Board:"_________" > Boards Manager..._**) which already have esp32 hardware library `INSTALLED`. Follow this [instruction](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) to install it.
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32.png" width="600"></a></p>



## Interfacing Hibiscus to Computer's USB Port

Connect the USB cable Type-C to Hibiscus Sense and Type-A to our computer. Hibiscus Sense comes with preset program to test on-board actuators and sensors. Should be by now we'll see the buzzer is buzzing, the RGB LED changing colors, the blue LED blinking and the reading of sensors at Serial Monitor (we have to open the Arduino IDE Serial Monitor to see the data). Suppose, you didn't see any reaction on the board you can contact Mr. Ariffin via [WhatsApp](https://api.whatsapp.com/send?phone=60177875232&text=Hi%20Mr.%20Ariffin,%20please%20help.%20My%20Hibiscus%20Sense,%20seems%20not%20working%20for%20the%20first%20time.) for help.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time.gif" width="600"></a></p>

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time-monitor.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 1: Control Blue LED on GPIO2 (Strobe Light Effect)

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-exercise-one.png" width="400"></a></p>

There is 1x blue LED labelled as `LED` on-board, as circled on the image above. The circuit of this LED is an **active-low circuit**, as shown in the schematic below, which the negative (-ve) terminal of this LED is connected to GPIO2, therefore we have to pull the GPIO2 to LOW state, in order to complete the circuit, then the light of the LED will turn ON. Otherwise, by pulling the GPIO2 to HIGH state, the light of the LED will turn OFF.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one.png" width="150"></a></p>
 
This is quite unusual behaviour, but it is good to learn how an electronic circuit could behave either way. Whereas, the usual circuit design is **active-high circuit**, where the positive (+ve) terminal of the LED connected to the GPIO2, as in the schematic below, instead of the negative (-ve) terminal of the LED connected to GPIO2, as in the schematic above. According to this type of circuit, we need to pull GPIO2 to HIGH state, to turn ON the LED, otherwise pull GPIO2 to LOW state, to turn OFF the LED.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one-a.png" width="150"></a></p>

Since, the blue LED circuit on Hibiscus Sense is active-low, we will program it as below:

**Complete Sketch**
```cpp
void setup() {
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.

}

void loop() {
  // strobe light effect, such on the aeroplane.
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);

  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(2000);
}
```

**Detail Sketch Explanations**

The LED is connected to `GPIO2`, we need to configure GPIO2 as `OUTPUT`.
```cpp
pinMode(2, OUTPUT);
```

In the `void loop()` function, the program start by turn ON the LED, as the ciruit is active-low, we use `LOW` state on GPIO2 to complete the LED circuit. Then `delay()` function to pause the program in milliseconds. Vice versa to turn OFF the LED.
```cpp
digitalWrite(2, LOW);
delay(100);
digitalWrite(2, HIGH);
delay(100);

digitalWrite(2, LOW);
delay(100);
digitalWrite(2, HIGH);
delay(2000);
```

Now, we can upload the complete sketch to ESP32, then observe the output. By observation, the output of the LED only have 2 states, which are ON and OFF, thus this output signal known as **`DIGITAL OUTPUT`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one-a.gif" width="600"></a></p>

**Interesting facts!** This exercise is mimicking the strobe light on an aeroplane during the night.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one.gif" width="300"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 2: Control Blue LED on GPIO2 (Glowing Light Effect)

In this exercise, we will use the same blue LED in [Exercise 1](https://github.com/myinvent/hibiscus-sense-arduino#exercise-1-control-blue-led-on-gpio2-strobe-light-effect), but producing glowing light effect, as the image shown below. Where the blue LED color will start from OFF and slowly glowing until it reach its maximum brightness and turn OFF again, repeatedly.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two.gif" width="300"></a></p>

As we know, the output signal from [Exercise 1](https://github.com/myinvent/hibiscus-sense-arduino#exercise-1-control-blue-led-on-gpio2-strobe-light-effect) is `DIGITAL OUTPUT`, where the output signal is either turn ON or turn OFF, but to achieve glowing light effect, we need an output signal that has ranges of values from minimum to maximum value.

What we need is the Pulse-Width Modulation (PWM), where the signal output that has been generated by the PWM, is almost **`ANALOG OUTPUT`**, but not a true sine wave analog output. PWM is a modulation technique which generates variable-width pulses in the duty cycle of digital signal (square wave), where in average over time, it is representing analog output signal, as shown in the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two-a.gif" width="500"></a></p>

With PWM output signal, we can control brightness of LEDs, the speed of motors, the heat of the heating elements, the vibration of piezo elements for buzzer loudness, the direction of the servo motors and modulated audio signal.

The great news is, ESP32 have 16 congifurable independent PWM channels, which can be configured to generate PWM signal on all GPIOs, except GPIO34 to GPIO39.

Prior to hands-on programming, let's discuss about the program to generate the PWM output signal.

Usually in any official Arduino boards or any compatible Arduino boards, we will use `analogWrite()` function to generate PWM signal. Since ESP32's PWM channels is configurable, it has 3 functions to configure and generate the PWM signal, which are:
1. `ledcSetup(_channel_, _frequency_, _resolution_)` setup function for PWM controller, with 3 arguments:
  - _channel_ the number of the PWM channel, from 0 to 15.
  - _frequency_ the PWM signal frequency, for LED is 5 kHz.
  - _resolution_ the PWM signal resolution, from 1 bit to 16 bits, for the LED we will use 8 bits resolution.
2. `ledcAttachPin(_gpio_, _channel_)` function to declare LED's GPIO number and the PWM channel, with 2 arguments:
  - _gpio_ the GPIO number for output of the PWM signal.
  - _channel_ the number of the PWM channel.
3. `ledcWrite(_channel_, _dutycycle_)` function to generate PWM signal outputs, with 2 arguments:
  - _channel_ the number of the PWM channel.
  - _dutycycle_ the PWM duty cycle value. For 8 bits resolutions, the value range from 0 - 255.

Again, to be remember, the blue LED circuit on Hibiscus Sense is active-low, so we will program the LED for glowing effect as follows:

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
    // ledcWrite() function will generate PWM output signal according to variable brightness value
    // 1st argument: PWM channel number.
    // 2nd argument: Tone frequency.
    ledcWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again
  delay(200);
}
```

**Detail Sketch Explanations**

In the `void setup()` function, there are two functions to be program, first to configure the PWM channelf using `ledcSetup()` function, with **_PWM channel `0`_**, **_PWM frequency `5 kHz`_** and **_`8 bits` PWM resolution_**. 
```cpp
ledcSetup(0, 5000, 8);
```

In the `void setup()` function, we also declare which GPIO to deliver the output of the PWM signal using `ledcAttachPin();` function, with **_GPIO number `2`_** where the blue LED is interfaced and **_PWM channel `0`_**.
```cpp
ledcAttachPin(2, 0);
```

Both function to configure the PWM channel and to declare GPIO for PWM output signal has been done. Now we can generate the PWM signal by using `ledcWrite()` function inside the `void loop` to control the brightness of the blue LED to produce glowing blue LED effect. Since the blue LED circuit is active-low, the PWM value _(from 255-0)_ needs to be automatically decremental 1 by 1 by, from 255 to 254, from 254 to 253, from 253 to 252 and so on until the value reach minimum PWM value, 0. Therefore, `for()` function is used to automatically generate decremental variable of PWM value from 255-0 as follows, where the `ledcWrite()` function is inside `for()` function:
```cpp
for(int brightness = 255; brightness >= 0; brightness--){   
  ledcWrite(0, brightness);
  delay(15);
}
```

Now, we can upload the complete sketch to ESP32, then observe the output. By observatoin, the output of the blue LED is repeated glowing light effect, which the results from decremental value of the PWM signal output.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two-b.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 3: Control Blue LED on GPIO2 (Breathing Light Effect)

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

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 4: Control Small Buzzer on GPIO13 (Melody)

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-four.png" width="300"></a></p>

Buzzer is a piezoelectrical electronic components, which generate tones when the piezo elements is vibrated based on given voltage supply, different voltage will produce different vibration, thus generating different tone. Since ESP32 has the ability to generate range of voltage using, the built-in PWM controllers, we can apply it on our small buzzer to generate tone.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-four-a.gif" width="400"></a></p>

On Hibiscus Sense, there is 1x small buzzer, labelled as `BUZZER` on-board, as circled on the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-four-b.png" width="400"></a></p>

The operating voltage of the small buzzer is ranging from 2-4V with rated voltage of 3V, the `(+ve) terminal` of the buzzer is connected to `GPIO13`, while the `(-ve) terminal` is connected to `GND`, as shown in the schematic below. The 3rd terminal of the buzzer is not connected.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-four.png" width="400"></a></p>

To produce the tone or melody from the buzzer, we need to write PWM functions to control the PWM output signal on GPIO13. In [Exercise 2]() and [Exercise 3]() we use `ledcWrite(_channel_, _dutycycle_)` function to control the brightness of the LEDs, while to generate the tone, ESP32 has other function known as `ledcWriteTone(_channel_, _note_)` function, with 2 arguments:
  - _channel_ the number of the PWM channel.
  - _note_ the the frequency of note. Example, Note D4 = 147 Hz. Click [here](https://github.com/myinvent/hibiscus-sense-arduino/blob/main/Exercise_04_Melody/tones.h) for available tones.

In this exercise, all the available note and its frequency to produce the tone, has been declared on a header file, titled `tones.h` as [here](https://github.com/myinvent/hibiscus-sense-arduino/blob/main/Exercise_04_Melody/tones.h) for available tones.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-four-c.png" width="500"></a></p>

Since we have notice, we need to use `ledcWriteTone()` function instead of `ledcWrite()` function to generate the PWM output signal for the buzzer to produce the tone, let's write the program as below:

**Complete Sketch**
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

**Detail Sketch Explanations**

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

Now, we can upload the complete sketch to ESP32. Once done uploading, we'll hear beeping sound.

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 5: Serial Communication (Hibiscus Sense & Computer)

Serial Communication is a communication process, receiving and transmitting data between two devices, such as **_computer to computer_** or **_microcontroller to computer_** or **_microcontroller to microcontroller_**, by implementing hardware protocol known as `UART (Universal Asynchronous Receiver/Transmitter)`. The data were sent/receive bit by bit sequentially by UART over two or one transmission line (wires), with configurables speed known as `baud-rate` or `bits-per-second` (bps): _9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600_.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five.gif" width="200"></a></p>

The two transmission lines of UART, known as `RX (receive)` and `TX (transmit)`. The transmission begin by transmitting the data from TX port of one UART controller to RX port of the other UART controller.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five-a.png" width="400"></a></p>

There are 3x UART controllers available in ESP32:
UART | RX  | RX  |
---- | --- | --- |
UART0 | GPIO3 | GPIO1
UART1 | GPIO9 | GPIO10
UART2 | GPIO16 | GPIO17

On Hibiscus Sense, UART0 has been interfaced to Silicon Labs CP2104, which enable us to make serial communication between computer and ESP32. The UART0 also used for uploading the program into the ESP32. _While, UART1 has been used for SPI flash for the ESP32 module and UART1 RX has been used for WS2812 RGB LED._

Although, the hardware serial is ready, it woudld not initialized, unless we program the ESP32 to initialized its serial hardware. In Arduino programming, the default library for serial communication, known as `Serial`. We can use **Serial** library to program the ESP32 for serial communication. There are 5 main functions in `Serial` library for serial communication, they are:
1. `Serial.begin(_baud-rate_)` function, with 1 argument:
  - _baud-rate_ the speed of serial communication.
2. `Serial.print()` function transmit the data and print the data on the Serial Monitor, with 1 / 2 arguments:
  - 1 arguments:
    - `Serial.print(88)` transmit and print "88"
    - `Serial.print(1.23456)` transmit and print "1.23" (default 2 decimal places)
    - `Serial.print('H')` transmit and print "H"
    - `Serial.print("Hello, hibiscus!")` transmit and print "Hello, hibiscus!"
  - 2 arguments (optional) `base number or decimal points`:
    - `Serial.print(88, BIN)` transmit and print "1011000"
    - `Serial.print(88, OCT)` transmit and print "130"
    - `Serial.print(88, DEC)` transmit and print "88"
    - `Serial.print(88, HEX)` transmit and print "58"
    - `Serial.print(1.23456, 0)` transmit and print "1"
    - `Serial.print(1.23456, 2)` transmit and print "1.23"
    - `Serial.print(1.23456, 4)` transmit and print "1.2345"
3. `Serial.println()` function same as `Serial.print()`, with additional character of newline.
4. `Serial.available()` function use to check if the data is available in the buffer (holds 64 bytes).
5. `Serial.read()`function use to read the data inside the serial receive buffer.

We have understand main `Serial` library functions, now let's write a program ESP32 can transmit incremental value to Arduino IDE's Serial Monitor. The program as below:

**Complete Sketch**
```cpp
// global variable named as counter with value 0
int counter = 0;

void setup() {
  // initialized ESP32 UART0 with speed 9600bps
  Serial.begin(9600);
}

void loop() {
  // increment variable counter's value by +1 on every loop.
  counter++;
  // transmit the variable counter's value to computer
  Serial.println(counter);
  // wait for 1 second before next action.
  delay(1000);
}
```

**Detail Sketch Explanations**

To create incremental value, we can use (+) plus operator as it is an _addition_ arithmetic operations. We can create a global variable with `initial value of 0` and `int` integer data type.
```cpp
int counter = 0;
```

In the `void setup()` function, firstly we need to initialize the hardware serial communication by calling `begin()` function of `Serial` object, with suitable baud-rate, most commonly used is `9600`.
```cpp
Serial.begin(9600);
```

In logical thinking, before we can submit any value we need to have the value first, before we can submit it, right? Therefore, in the `void loop()` function, the first thing to do, is to generate _incremental value_ of variable `counter`, applying (++) arithmetic operations, representing +1 to the previous value of variable counter. Example of previous value of `counter` is `0` then add it by +1, the latest value of variable counter is 1, as thing process is inside the `void loop()` function, the variable counter's value incrementally by 1 each loop.
```cpp
counter++;
```

To transmit the value of variable counter with newline, we use `println()` function of `Serial` object, to do the task by refering the variable counter on the argument of `println()` function.
```cpp
Serial.println(counter);
```

Pause the task for a second before continue to the next action.
```cpp
delay(1000);
```

Now, we can upload the complete sketch to ESP32, once done uploading open the Serial Monitor. By observation, we can see an incremental value with newline is printed on the Arduino IDE Serial Monitor.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five-b.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 6: Monitor Pushbutton Status on GPIP0 (LED ON/OFF)

Pushbutton is a momentary switch that closed the circuit during press of the button, while the button is released, the circuit disconnected, such as shown in the animation below. It is not a toggle switch, where it has ON and OFF position. Pushbutton usually used to act as an input to trigger the system.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-six.gif" width="300"></a></p>

On Hibiscus Sense, there are two pushbutton:
1. **`RST`** push the button to reset the ESP32 program.
2. **`IO0`** connected to GPIO0.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-six-a.png" width="400"></a></p>

Both pushbutton in Hibiscus Sense applying [pull-up resistor](https://learn.sparkfun.com/tutorials/pull-up-resistors/all), to prevent floating voltage with capacitor to fix [debouncing effect](https://www.analog.com/en/technical-articles/better-way-to-push-your-buttons.html) of pushbutton. The circuit is complete when we push the **`IO0`** pushbutton, then ESP32 saw `LOW` state at `GPIO0`, because `GND` is connected to the junction of `GPIO0` in the circuit, as shown in the schematic below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-six.png" width="300"></a></p>

Somehow, if a pushbutton circuit is applying pull-down resistor, as shown in the schematic below. ESP32 saw `HIGH` state at `GPIO0` when the IO0 pushbutton is pressed, because `3.3V` is connected to the junction of `GPIO0`. _This is **NOT** the circuit on Hibiscus Sense._

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-six-a.png" width="300"></a></p>

Since we know that ESP32 will sense `LOW` state at `GPIO0` during pushbutton pressed, so the program as follows:

**Complete Sketch**
```cpp
void setup() {
  pinMode(0, INPUT);  // declaring GPIO0 as an INPUT pin.
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.

}

void loop() {
  // we use if() function to compare the GPIO0 reading state with the LOW state.
  // if the GPIO0 reading is LOW, light ON the LED on GPIO2 with LOW state.
  // else means, the GPIO0 reading is HIGH, light OFF the LED on GPIO2 with HIGH state.
  int pbstatus = digitalRead(0);
  if(pbstatus == LOW) digitalWrite(2, LOW);
  else digitalWrite(2, HIGH);
  
}
```

**Detail Sketch Explanations**

In the `void setup()` function we declare two `pinMode()` function:
1. To declare GPIO0 as an INPUT pin, connected to the Pushbutton.
2. To declare GPIO2 as an OUTPUT pin, connected to the blue LED.
```cpp
pinMode(0, INPUT);  // declaring GPIO0 as an INPUT pin.
pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.
```

In the `void loop()` function we want to repeatedly monitor the state of GPIO0, either `LOW` or `HIGH` depending the action happen on the pushbutton, either `pressed` or `release`.
1. Create local variable named as `pbstatus` to store the current state of GPIO.
```cpp
 int pbstatus = digitalRead(0);
```
2. Applying `if()` function to **compare**, either the value of `pbstatus` variable _equal to_ `LOW` or else (`HIGH`). If the `pbstatus == LOW` turn ON the LED and if `pbstatus` equal to other than `LOW` turn OFF the LED.
```cpp
if(pbstatus == LOW) digitalWrite(2, LOW);
else digitalWrite(2, HIGH);
```

Now, we can upload the complete sketch to ESP32. Now we'll see the blue is turn OFF, as it will only turn ON once we pressed the IO0 pushbutton.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-six-b.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>




## Exercise 7: Control RGB LED on GPIO16

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

**Complete Sketch**
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

**Detail Sketch Explanations***

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

Now, we can upload the complete sketch to ESP32, then observe the output. By observation, the colour output from RGB LED is magenta.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-seven-c.jpg" width="500"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 8: Monitor Proximity Value from APDS9960

APDS9960 is an advance sensor offering digital proximity, ambient light, RGB and gesture sensor in a very small package. amazing, right? The advance integrated IR LED and driver on the sensor, allows it to measure proximity (up to a few centimeters) with 8-bit resolution (value: 0-255). Below is an illustration of IR LED acts as proximity sensor.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight.gif" width="500"></a></p>

The built-in UV and IR blocking filters, allows APDS9960 to sense ambient light and RGB color. While, with four separate diodes sensitive to different directions and ambient light rejectino, allows it to sense gesture.

APDS9960 communication protocol is I2C. Therefore, we can interface it to ESP32 using I2C, to acquire its available measurement.

There is 1x APDS9960 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x39`**. The arrow is pointing towards gesture sensing **`UP`** direction.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-a.png" width="400"></a></p>

To acquire sensing information from APDS9660, we need to use [Adafruit_APDS9960](https://github.com/adafruit/Adafruit_APDS9960) library, as it will helps shorten the time consuming development and focus on the objective, which to sense the proximity value. Prior to program the ESP32, we need to install the library from Arduino IDE's Library Manager, as on the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-b.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

**Complete Sketch**
```cpp
// include the Adafruit_APDS9960 header file.
#include <Adafruit_APDS9960.h>

// instance of the Adafruit_APDS9960 class named as apds.
Adafruit_APDS9960 apds;

void setup() {
  
  // Initialize the serial communication with baud rate 9600bps.
  Serial.begin(9600);
  // Initialize APDS9960 sensor and if the connection is not successful,
  // print the failed status to the Serial Monitor.
  if (!apds.begin()){
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  // enable the proximity mode on APDS9960
  apds.enableProximity(true);
}

void loop() {

  // to acquire APDS9960 proximity value,
  // we need to call apds.readProximity() function from apds instance.
  // The proximity values range from 0-255, 255 is the nearest proximity value.

  Serial.print("Proximity: ");
  Serial.println(apds.readProximity());

  Serial.println("===============");

  delay(500);

}
```

Now, we can upload the complete sketch to ESP32, once done uploading open the Serial Monitor and try to hover our hands up and down above the sensor. By observation, we can see on the Serial Monitor a proximity in an 8-bit chaning based on up and down of our hand. The closer the object, the higher the proximity value.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-c.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 9: Monitor Gesture Direction from APDS9960

In this exercise, we will use same APDS9960 from [Exercise 8](https://github.com/myinvent/hibiscus-sense-arduino#exercise-8-monitor-proximity-value-from-apds9960) with different application of sensing gesture direction, the sketch as follows:

**Complete Sketch**

```cpp
// include the Adafruit_APDS9960 header file.
#include <Adafruit_APDS9960.h>

// instance of the Adafruit_APDS9960 class named as apds.
Adafruit_APDS9960 apds;

void setup() {
  // Initialize the serial communication with baud rate 9600bps.
  Serial.begin(9600);
  // Initialize APDS9960 sensor and if the connection is not successful,
  // print the failed status to the Serial Monitor.
  if (!apds.begin()){
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  // enable the proximity mode on APDS9960
  apds.enableProximity(true);
  // enable the gesture mode on APDS9960
  apds.enableGesture(true);
}

void loop() {
  // to acquire APDS9960 gesture direction,
  // we need to call apds.readGesture() function from apds instance.

  uint8_t gesture = apds.readGesture();

  if(gesture == APDS9960_DOWN) Serial.println("Gesture Direction: DOWN");
  if(gesture == APDS9960_UP) Serial.println("Gesture Direction: UP");
  if(gesture == APDS9960_LEFT) Serial.println("Gesture Direction: LEFT");
  if(gesture == APDS9960_RIGHT) Serial.println("Gesture Direction: RIGHT");
  
}
```

Now, we can upload the complete sketch to ESP32, once done uploading open the Serial Monitor. To try the gesture:
1. Activate the proximity by hovering our hands close as possible above the APDS9960.
2. Make gesture by hivering our hands into direction of UP, DOWN, RIGHT and LEFT.

We should see the direction on the Serial Monitor, as on the image below:

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-nine.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>


## Exercise 10: Monitor Environmental Value using BME280

BME280 is an environmental sensor with the ability to sense altitude, barometric pressure, humidity and temperature. It is great for indoor environmental monitoring. It has both communication protocol I2C and SPI.

There is 1x BME280 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x77`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten.png" width="400"></a></p>

This sensor is manufactured by Bosch, low-cost sensing solution:
1. Altitude with ±1 meter accuracy.
2. Barometric pressure with ±1 hPa absolute accuraccy.
3. Humidity with ±3%RH accuracy.
4. Temperature with ±1.0°C accuracy.

To acquire sensing information from BME280, we need to use [Adafruit_BME280](https://github.com/adafruit/Adafruit_BME280_Library) library, as it will helps shorten the time consuming development and focus on the objective, which to sense the proximity value. Prior to program the ESP32, we need to install the library from Arduino IDE's Library Manager, as on the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten-a.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

```cpp
// include the Adafruit_BME280 header file.
#include <Adafruit_BME280.h>

// instance of the Adafruit_BME280 class named as bme.
Adafruit_BME280 bme;

void setup() {
  
  // Initialize the serial communication with baud rate 9600bps.
  Serial.begin(9600);
  // Initialize BME280 sensor and if the connection is not successful,
  // print the failed status to the Serial Monitor.
  if (!bme.begin()){
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }
  
}

void loop() {

  // to acquire BME280 data parameters,
  // there are four function need to be called from bme instance:
  // 2. bme.readAltitude(), this function will return altitude value in meters.
  // 1. bme.readPressure(), this function will return barometric pressure value in Pascals.
  // 2. bme.readHumidity(), this function will return humidity value in % Relative Humidity.
  // 2. bme.readTemperature(), this function will return temperature value in celcius.

  Serial.print("Approx. Altitude: ");
  Serial.print(bme.readAltitude(1013.25));
  Serial.println(" m");

  Serial.print("Barometric Pressure: ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %RH");
  
  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.println("==================================");

  delay(500);
  
}
```

Now, we can upload the complete sketch to ESP32, once done uploading open the Serial Monitor and we'll see latest value altitude, barometric pressure, humidity and temperature.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Exercise 11: Monitor 6-axis Motion Tracking using MPU6050

MPU6050 is a 6-axis motion tracking sensor with the ability to sense:
1. 3-axis accelerometer, the gravitational acceleration.
2. 3-axis gyroscope, the rotational velocity.
3. Temperature

There is 1x MPU6050 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x68`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eleven.png" width="400"></a></p>

To acquire sensing information from MPU6050, we need to use [Adafruit_MPU6050](https://github.com/adafruit/Adafruit_MPU6050) library, as it will helps shorten the time consuming development and focus on the objective, which to sense the proximity value. Prior to program the ESP32, we need to install the library from Arduino IDE's Library Manager, as on the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten-a.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

```cpp
// include the Adafruit_MPU6050 header file.
#include <Adafruit_MPU6050.h>

// instance of the Adafruit_MPU6050 class named as mpu.
Adafruit_MPU6050 mpu;

// sensor event object variable declaration:
// a for accelerometer values
// g for gyroscope values
// temp for temperature
sensors_event_t a, g, temp;

void setup() {
  
  // Initialize the serial communication with baud rate 9600bps.
  Serial.begin(9600);
  // Initialize MPU6050 sensor and if the connection is not successful,
  // print the failed status to the Serial Monitor.
  if (!mpu.begin()){
    Serial.println("Failed to find Hibiscus Sense MPU6050 chip");
  }

}

void loop() {

  // to acquire MPU6050 accelerometer, gyroscope and temperature values,
  // we need to call mpu.getEvent() function from mpu instance.
  // in the function there are three arguments:
  // 1st argument: return of accelerometer value in reference to sensor event object: a.
  // 2nd argument: return of gyroscope value in reference to sensor event object: g.
  // 3rd argument: return of temperature value in reference to sensor event object: temp.

  mpu.getEvent(&a, &g, &temp);

  // To display the individual axis of accelerometer values from a object, in m/s^2,
  // we need to call the axis variable from nested object of a, as below:
  Serial.print("Acceleration X:");
  Serial.print(a.acceleration.x);
  Serial.print(", Y:");
  Serial.print(a.acceleration.y);
  Serial.print(", Z:");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  // To display the individual axis of gyroscope values from g object, in rad/s,
  // we need to call the axis variable from nested object of g, as below:
  Serial.print("Rotation X:");
  Serial.print(g.gyro.x);
  Serial.print(", Y:");
  Serial.print(g.gyro.y);
  Serial.print(", Z:");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  // To display the temperature values from temp object, in celcius,
  // we need to call the temperature variable from nested object of temp, as below:
  Serial.print("Temperature:");
  Serial.print(temp.temperature);
  Serial.println(" *C");

  Serial.println("=============================================");

  delay(500);
  
}
```

Now, we can upload the complete sketch to ESP32, once done uploading open the Serial Monitor and move around Hibiscus Sense. Then, we'll see latest value 3-axis accelerometer, 3-axis gyroscope and temperature.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eleven.gif" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>



## Image Credits
- _Isaac Low on Quora_
- _Ben Ot on Wikimedia_
- _Explore Embedded_
- _DeStress Monday on Giphy_
- _Mouser_
- _Arduino Getting Started_
- _Cable Depot_
- _Analog Devices_
- _Circuit Digest_
- _Matthew L. Beckler_
- _Anonymous on ColorOS_