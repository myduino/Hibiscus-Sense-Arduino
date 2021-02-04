# Hibiscus Sense ESP32 Arduino Tutorial

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-logo.png" width="300"></a></p>
<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense.png" width="400"></a></p>

> Whenever you are thinking of quick IoT hardware prototyping / development, just grab **Hibiscus Sense** and right away focus on programming.

## Table of Content
- [Introduction](https://github.com/myinvent/hibiscus-sense-arduino#introduction)
- [Hibiscus Sense Features](https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-features)
- [Hibiscus Sense Pinout Diagram](https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-pinout-diagram)
- [Learning Material Preparation](https://github.com/myinvent/hibiscus-sense-arduino#learning-material-preparation)
- [Interfacing Hibiscus to Computer's USB Port](https://github.com/myinvent/hibiscus-sense-arduino#interfacing-hibiscus-to-computers-usb-port)
- [Tutorial 1: Control Blue LED on GPIO2](https://github.com/myinvent/hibiscus-sense-arduino#exercise-1-control-blue-led-on-gpio2)

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

Hibiscus Sense, comes with **USB Type-C** to power up the board (5V supply from the computer's USB) and to program the ESP32 microcontroller. On-board also has USB-to-Serial converter **Silicon Labs CP2104** with **automatic bootloader reset**, so we don’t have to press the RESET button each time to upload the program into the microcontroller.

Despite, we can program ESP32 using other programming language and it's tools, in this exercise we will focus on using [Arduino](https://www.arduino.cc/) as the learning and prototyping platform.

## Hibiscus Sense Features

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-features.png" width="900"></a></p>

## Hibiscus Sense Pinout Diagram

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-pinout.png" width="900"></a></p>

- **Blue LED** is connected to `GPIO2` ESP32 microcontroller.
- **Small Buzzer** is connected to `GPIO13` ESP32 microcontroller.
- **WS2812 RGB LED** is connected to `GPIO16` ESP32 microcontroller.
- All GPIO can generate digital input/output (3.3V) and PWM signal output, except `GPIO34-GPIO39` because it is an input pin only.
- ESP32 `VSPI` is complete **MISO** `GPIO19`, **MOSI** `GPIO32`, **CLK** `GPIO18` and **CS** `GPIO5`.
- ESP32 `I2C` **SDA** `GPIO21` and **SCL** `GPIO22`, without pullup resistor.
- **Sensors**: **APDS9960**, **BME280** and **MPU6050** interfaced to the `I2C` ESP32 microcontroller, respectively I2C address: `0x39`, `0x77` and `0x68`.
- Avoid to use `ADC2` channel while using WiFi.
- Each GPIO absolute maximum current drawn only 16mA.
- Board measurement including header in mm: 58.7 x 27 x 13.3 (length x width x height).
- Package measurement in mm: 71.8 x 35.5 x 20.4 (length x width x height).

## Learning Material Preparation

Prior to start learning to control the actuators and acquire data from the sensors on Hibiscus Sense using Arduino programming tool and language, we have to make sure all learning material is ready, as below:
1. Hibiscus Sense and a USB cable Type-A to Type-C _(suppose your computer only have Type-C USB port, you can also use USB cable Type-C to Type-C)_. If you don't have one, you are always welcome to purchase it from [Myduino](https://myduino.com/product/myd-036/)
2. A computer with Arduino IDE installed, if you don't have it please download it from here: [Windows](https://downloads.arduino.cc/arduino-1.8.13-windows.exe) / Linux [32-bit](https://downloads.arduino.cc/arduino-1.8.13-linux32.tar.xz), [64-bit](https://downloads.arduino.cc/arduino-1.8.13-linux64.tar.xz), [ARM 32-bits](https://downloads.arduino.cc/arduino-1.8.13-linuxarm.tar.xz) [ARM 64-bits](https://downloads.arduino.cc/arduino-1.8.13-linuxaarch64.tar.xz) / [Mac OSX](https://downloads.arduino.cc/arduino-1.8.13-macosx.zip) and install it on your computer.
3. [Arduino-ESP32](https://github.com/espressif/arduino-esp32) hardware library installed. Below is screenshot, showing the `Arduino IDE Boards Manager` (Arduino IDE Menu: **_Tools > Board:"_________" > Boards Manager..._**) which already have esp32 hardware library `INSTALLED`. If you don't have it, please follow this [instruction](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) to install it.
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32.png" width="600"></a></p>

## Interfacing Hibiscus to Computer's USB Port

Connect the USB cable Type-C to Hibiscus Sense and Type-A to our computer. Hibiscus Sense comes with preset program to test on-board actuators and sensors, should be by now we'll see the buzzer is buzzing, the RGB LED changing colors, the blue LED blinking and the reading of sensors at Serial Monitor (we have to open the Arduino IDE Serial Monitor to see the data). Suppose, you didn't see any reaction on the board you can contact Mr. Ariffin via [WhatsApp](https://api.whatsapp.com/send?phone=60177875232&text=Hi%20Mr.%20Ariffin,%20please%20help.%20My%20Hibiscus%20Sense,%20seems%20not%20working%20for%20the%20first%20time.) for help.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time.gif" width="600"></a></p>

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time-monitor.gif" width="600"></a></p>

## Exercise 1: Control Blue LED on GPIO2 (Strobe Light Effect)

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-exercise-one.png" width="400"></a></p>

There is 1x blue LED labelled as `LED` on-board, as circled on the image above. The circuit of this LED is an **active-low circuit**, as shown in the schematic below, which the negative (-ve) terminal of this LED is connected to GPIO2, therefore we have to pull the GPIO2 to LOW state, in order to complete the circuit, then the light of the LED will turn ON. Otherwise, by pulling the GPIO2 to HIGH state, the light of the LED will turn OFF.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one.png" width="150"></a></p>
 
This is quite unusual behaviour, but it is good to learn how an electronic circuit could behave either way. Whereas, the usual circuit design was **active-high circuit**, where the positive (+ve) terminal of the LED connected to the GPIO2, as in the schematic below, instead of the negative (-ve) terminal of the LED connected to GPIO2, as in the schematic above. According to this type of circuit, we need to pull GPIO2 to HIGH state, to turn ON the LED, otherwise pull GPIO2 to LOW state, to turn OFF the LED.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one-a.png" width="150"></a></p>

Since, the blue LED circuit on Hibiscus Sense is active-low, we will program it as below:

**Complete Sketch**
```
void setup() {
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.

}

void loop() {
  // stobe light effect, such on the aeroplane.
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

**Detail Code Explanations**

The LED is connected to `GPIO2`, which we need to configure GPIO2 as `OUTPUT`.
```
pinMode(2, OUTPUT);
```

In the `void loop()` function, the program start by turning the LED ON, as the ciruit is active-low, we use `LOW` state on GPIO2 to complete the LED circuit. Then `delay()` function to pause the program in milliseconds. Vice versa to turn OFF the LED.
```
digitalWrite(2, LOW);
delay(100);
digitalWrite(2, HIGH);
delay(100);

digitalWrite(2, LOW);
delay(100);
digitalWrite(2, HIGH);
delay(2000);
```

Now, we can upload the complete sketch to ESP32, then observe the output. By oversation, the output of the LED only have 2 states, which are ON and OFF, thus this output signal is what we called, as **`DIGITAL OUTPUT`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one-a.gif" width="600"></a></p>

**Interesting facts!** The LED output of the program is actually, an example of strobe light, which we saw on an airplane during the night.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one.gif" width="300"></a></p>

## Exercise 2: Control Blue LED on GPIO2 (Glowing Light Effect)

In this exercise, we will use the same blue LED in Tutorial 1, then only changes happen in this exercise are the program will be replace for an output of glowing light effect, as the image shown below. Where the blue LED color will start from OFF and slowly glowing until it reach maximum light ON and turn OFF again and repeat the process again and again.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two.gif" width="300"></a></p>

As we know, the output signal from Tutorial 1 is `DIGITAL OUTPUT`, where the output signal is either turn ON or turn OFF, but to achieve glowing light effect, we cannot rely on digital output signal anymore. Therefore we need a signal that has ranges of output signal from minimum to maximum value.

What we need is the Pulse-Width Modulation (PWM), whereas the signal output that has been generated by the PWM, most of us also called it as **`ANALOG OUTPUT`**, despite it is not a true sine wave analog output. PWM is a modulation technique which generates variable-width pulses in the duty cycle of digital signal (square wave), which in average over time, representing analog output signal, as shown in the image below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two-a.gif" width="500"></a></p>

The great news is, ESP32 microcontroller have 16 channels congifurable independent PWM controller, which can be configured to generate PWM signal on all GPIOs available on ESP32, except GPIO34 to GPIO39.

Prior to hands-on programming, let's dicsuss about the program to control the PWM output signal. Usually in any official Arduino boards or any compatible Arduino boards, we will use `analogWrite()` function to generate PWM signal, since ESP32's PWM controller is configurable, does it has 3 functions to control the PWM output signal, which are:
1. `ledcSetup(_channel_, _frequency_, _resolution_)` setup function for PWM controller, with 3 arguments:
  - _channel_ the number of the PWM channels, from 0 to 15.
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
```
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
```

**Detail Code Explanations**

In the `void setup()` function, we configure the PWM configuration using `ledcSetup()` function, with **_PWM channels `0`_**, **_PWM frequency `5 kHz`_** and **_`8 bits` PWM resolution_**. 
```
ledcSetup(0, 5000, 8);
```

In the `void setup()` function, we also declare which GPIO to choose for PWM signal output using `ledcAttachPin();` function, with **_GPIO number `2`_** where the blue LED is interfaced and **_PWM channels `0`_**.
```
ledcAttachPin(2, 0);
```

Both function to configure the PWM controller and to declare GPIO for PWM output signal has been done, now we can generate the PWM signal by using `ledcWrite()` function inside the `void loop` to produce repeatedly glowing blue LED effect. To produce glowing effect, since the blue LED circuit is active-low, the PWM value _(from 0-255)_ needs to be automatically decremental 1 by 1 by, from 255 to 254, from 254 to 253, from 253 to 252 and so on until the value reach its minimum, which is 0. Therefore, `for()` function is used to automatically generate decremental variable of PWM value from 255-0 as follows, where the `ledcWrite()` function is inside `for()` function:
```
for(int brightness = 255; brightness >= 0; brightness--){   
  ledcWrite(0, brightness);
  delay(15);
}
```

Now, we can upload the complete sketch to ESP32, then observe the output. By oversation, the output of the blue LED is glowing effect, which the results from variable decremental PWM signal output.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-two-b.gif" width="600"></a></p>