# Hibiscus Sense ESP32 Arduino Tutorial

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense.png" width="400"></a></p>

[Hibiscus Sense](https://myduino.com/product/myd-036/) is an Internet of Things (IoT) development board, powered by the mighty and popular dual-core [ESP32](https://www.espressif.com/en/products/socs/esp32) microcontroller, which on-board equipped with:
- 3 sensors:
  - APDS9960: an environment sensor, which sense *proximity, RGB* and *gesture*.
  - BME280: an environment sensor, which sense the *altitude, barometric pressure, humidity* and *temperature*.
  - MPU6050: 6-axis motion tracking sensor, which sense *3-axis gravitational acceleration, 3-axis rotational velocity* and *temperature*.
- 3 actuators:
  - Buzzer: short distance small buzzer.
  - LED & RGB LED: blue LED and WS2812 RGB LED.

Comes with USB Type-C to powered the board with 5V and to program the ESP32 microcontroller, which on-board has USB-to-Serial converter [Silicon Labs CP2104](https://www.silabs.com/interface/usb-bridges/classic/device.cp2104) with automatic bootloader reset, so we don’t have to press the RESET button each time to upload the program into the microcontroller.

Despite, we can program ESP32 using other programming language and it's tools, in this tutorial we will focus on using [Arduino](https://www.arduino.cc/) as the prototyping platform.

## Hibiscus Sense Features

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-features.png" width="800"></a></p>

## Hibiscus Sense Pinout Diagram

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-pinout.png" width="800"></a><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-precaution.png" width="800"></a></p>

- Small Buzzer is connected to `GPIO13` ESP32 microcontroller.
- Blue LED is connected to `GPIO2` ESP32 microcontroller.
- WS2812 RGB LED is connected to `GPIO16` ESP32 microcontroller.
- Sensors: APDS9960, BME280 and MPU6050 is interfaced to the `I2C` ESP32 microcontroller.