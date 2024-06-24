# Hibiscus Sense ESP32 Arduino Tutorial (English)

<p align="right">
  <a href="https://myduino.com/product/myd-036/"><img src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fmyinvent%2Fhibiscus-sense-arduino&count_bg=%2379C83D&title_bg=%23555555&icon=powerbi.svg&icon_color=%23E7E7E7&title=hits&edge_flat=false"/></a>
</p>

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-logo.png" width="300"></a></p>
<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense.png" width="400"></a></p>

> *Whenever you are thinking of quick IoT (Internet of Things) hardware prototyping / development, just grab [**Hibiscus Sense**](https://myduino.com/product/myd-036/) and focus on programming  :sunglasses:*

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

Although, we can program ESP32 using other programming language such as C, C++, [Micropython](https://micropython.org/), [Rust](https://github.com/esp-rs/rust), or even with RTOS (Real Time Operating System)  [FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html). However, in this tutorial we will be using [Arduino](https://www.arduino.cc/) as the learning and prototyping platform.

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
- Each GPIO absolute maximum current drawn only 40mA.
- Board measurement including header in mm: 58.7 x 27 x 13.3 (length x width x height).
- Package measurement in mm: 71.8 x 35.5 x 20.4 (length x width x height).

## Learn How to Program Hibiscus Sense using Arduino

**Important Notice:** _The example sketch in the exercises below, is based on the latest Arduino ESP32 Core version 3.0.0. So, if you are experience user in Arduino ESP32, please update the core to the latest version, before you can use the following example sketch. You can get more information from the [Arduino ESP32 v2.x to v3.x Migration Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html)_

You can clone or download this repo into your PC and open the exercise example sketch on the Arduino IDE. It is always recommended to begin with the hands-on learning preparation.

Below is the **Table of Contents** of the exercises.

- [Hands-On Learning Preparation](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_00_Learning_Preparation)
- [Exercise 01: Control Blue LED on GPIO2 (Strobe Light Effect)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_01_Strobe_Light)
- [Exercise 02: Control Blue LED on GPIO2 (Glowing Light Effect)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_02_Glowing_Light)
- [Exercise 03: Control Blue LED on GPIO2 (Breathing Light Effect)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_03_Breathing_Light)
- [Exercise 04: Control Small Buzzer on GPIO13](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_04_Melody)
- [Exercise 05: Serial Communication (Hibiscus Sense & Computer)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_05_Serial_Communication)
- [Exercise 06: Monitor Pushbutton Status on GPIP0 (LED ON/OFF)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_06_Pushbutton)
- [Exercise 07: Control RGB LED on GPIO16](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_07_RGB_LED)
- [Exercise 08: Monitor Proximity Value from APDS9960](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_08_APDS9960_Proximity)
- [Exercise 09: Monitor Hand Gesture Direction using APDS9960](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-09:-Monitor-Gesture-Directionhttps://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_09_APDS9960_Gesture)
- [Exercise 10: Monitor Environmental Value using BME280](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_10_BME280)
- [Exercise 11: Monitor 6-Axis Motion Tracking using MPU6050](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_11_MPU6050)
- [Exercise 12: IoT Application using Blynk IoT Platform](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_12_IoT_Blynk)
- [Exercise 13: IoT Application using Favoriot IoT Platform (Secure HTTP Protocol)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_13_IoT_FavoriotHTTPS)
- [Exercise 14: IoT Application using Favoriot IoT Platform (Secure MQTT Protocol)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_14_IoT_FavoriotMQTTS)
- [Exercise 15: IoT Application using Favoriot IoT Platform (CoAP Protocol)](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_15_IoT_FavoriotCoAP)

## Exercises Image Credits
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
