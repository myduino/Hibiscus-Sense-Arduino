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

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-features.png" width="900"></a></p>

## Hibiscus Sense Pinout Diagram

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-pinout.png" width="900"></a></p>

- **Small Buzzer** is connected to `GPIO13` ESP32 microcontroller.
- **Blue LED** is connected to `GPIO2` ESP32 microcontroller.
- **WS2812 RGB LED** is connected to `GPIO16` ESP32 microcontroller.
- All GPIO can generate PWM signal output, except `GPIO34-GPIO39` because it is an input pin only.
- ESP32 `VSPI` is complete **MISO** `GPIO19`, **MOSI** `GPIO32`, **CLK** `GPIO18` and **CS** `GPIO5`.
- ESP32 `I2C` **SDA** `GPIO21` and **SCL** `GPIO22`, without pullup resistor.
- **Sensors**: **APDS9960**, **BME280** and **MPU6050** interfaced to the `I2C` ESP32 microcontroller, respectively I2C address: `0x39`, `0x77` and `0x68`.
- Avoid to use `ADC2` channel while using WiFi.
- Each GPIO absolute maximum current drawn only 16mA.

