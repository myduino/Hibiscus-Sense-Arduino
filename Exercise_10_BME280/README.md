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

Now, you can upload the complete sketch to ESP32, once done uploading open the Serial Monitor and we'll see latest value altitude, barometric pressure, humidity and temperature.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-ten.gif" width="600"></a></p>

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>