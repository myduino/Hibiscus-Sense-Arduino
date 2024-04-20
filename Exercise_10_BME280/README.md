# Exercise 10: Monitor Environmental Value using BME280

The aim of this exercise is to learn how to measure relative humidity, altitude, barometric pressure and ambient temperature using the BME280 sensor.

BME280 is an environmental sensor, developed by [Bosch Sensortec](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/) that can measure **`relative humidity`**, **`altitude`**, **`barometric pressure`** and **`ambient temperature`**. It is good for indoor environmental monitoring application. **Note**: *Given its close proximity to the microcontroller, the BME280's temperature measurement may be affected by the heat dissipated from the microcontroller.*

It has both communication protocol I2C and SPI.

There is 1x BME280 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x77`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten.png" width="400"></a></p>

BME280 measurement specifications:
1. Relative humidity with ±3%RH accuracy.
2. Altitude with ±1 meter accuracy.
3. Barometric pressure with ±1 hPa absolute accuraccy.
4. Ambient temperature with ±1.0°C accuracy.

## Install Adafruit BME280 Library
Let's use [Adafruit_BME280](https://github.com/adafruit/Adafruit_BME280_Library) library, to easily program the ESP32 to read the environmental value from the BME280 sensor. Following the image below:
1. On the Arduino IDE, go to the Library Manager.
2. Search for **`adafruit bme280`**.
3. Look for ***Adafruit BME280 Library** by Adafruit* and click the **INSTALL** button and wait until the installation process is done, until the status on the library is *`2.2.x installed`*.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten-a.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

## Complete Sketch

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

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32. Once done uploading open the Serial Monitor and we'll see latest value altitude, barometric pressure, humidity and temperature.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten.gif" width="600"></a></p>

## Further Experiment
You can adjust the sampling rate or other settings of the BME280 sensor or combine the environmental data with other sensors or actuators for more complex projects.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>