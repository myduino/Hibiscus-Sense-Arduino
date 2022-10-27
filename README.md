# Hibiscus Sense ESP32 Arduino Tutorial (English)

<p align="right">
  <a href="https://myduino.com/product/myd-036/"><img src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fmyinvent%2Fhibiscus-sense-arduino&count_bg=%2379C83D&title_bg=%23555555&icon=powerbi.svg&icon_color=%23E7E7E7&title=hits&edge_flat=false"/></a>
</p>

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-logo.png" width="300"></a></p>
<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense.png" width="400"></a></p>

> Whenever you are thinking of quick IoT (Internet of Things) hardware prototyping / development, just grab [**Hibiscus Sense**](https://myduino.com/product/myd-036/) and focus on programming  :sunglasses:

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
- Each GPIO absolute maximum current drawn only 16mA.
- Board measurement including header in mm: 58.7 x 27 x 13.3 (length x width x height).
- Package measurement in mm: 71.8 x 35.5 x 20.4 (length x width x height).



## Learn How to Program Hibiscus Sense using Arduino IDE

- [Introduction to Hibiscus Sense](https://github.com/myinvent/hibiscus-sense-arduino/wiki/01.-Introduction-to-Hibiscus-Sense)
- [Learning Material Preparation](https://github.com/myinvent/hibiscus-sense-arduino/wiki/02.-Learning-Material-Preparation)
- [Connect Hibiscus Sense to Computer's USB Port](https://github.com/myinvent/hibiscus-sense-arduino/wiki/03.-Connect-Hibiscus-Sense-to-Computer's-USB-Port)
- [Exercise 1: Control Blue LED on GPIO2 (Strobe Light Effect)](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-01:-Control-Blue-LED-on-GPIO2-(Strobe-Light-Effect))
- [Exercise 2: Control Blue LED on GPIO2 (Glowing Light Effect))](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-02:-Control-Blue-LED-on-GPIO2-(Glowing-Light-Effect))
- [Exercise 3: Control Blue LED on GPIO2 (Breathing Light Effect)](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-03:-Control-Blue-LED-on-GPIO2-(Breathing-Light-Effect))
- [Exercise 4: Control Small Buzzer on GPIO13](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-04:-Control-Small-Buzzer-on-GPIO13-(Melody))
- [Exercise 5: Serial Communication (Hibiscus Sense & Computer)](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-05:-Serial-Communication-(Hibiscus-Sense-&-Computer))
- [Exercise 6: Monitor Pushbutton Status on GPIP0 (LED ON/OFF)](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-06:-Monitor-Pushbutton-Status-on-GPIP0-(LED-ON-OFF))
- [Exercise 7: Control RGB LED on GPIO16](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-07:-Control-RGB-LED-on-GPIO16)
- [Exercise 8: Monitor Proximity Value from APDS9960](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-08:-Monitor-Proximity-Value-from-APDS9960)
- [Exercise 9: Monitor Gesture Direction using APDS9960](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-09:-Monitor-Gesture-Direction-from-APDS9960)
- [Exercise 10: Monitor Environmental Value using BME280](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-10:-Monitor-Environmental-Value-using-BME280)
- [Exercise 11: Monitor 6-axis Motion Tracking using MPU6050](https://github.com/myinvent/hibiscus-sense-arduino#exercise-11-monitor-6-axis-motion-tracking-using-mpu6050)
- [Exercise 12: IoT using Blynk](https://github.com/myinvent/hibiscus-sense-arduino/wiki/Exercise-12:-Internet-of-Things,-Blynk)
- Exercise 13: IoT using Favoriot

## WiKi Image Credits
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
