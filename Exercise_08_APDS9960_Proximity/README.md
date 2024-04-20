# Exercise 08: Monitor Proximity Value from APDS9960

The aim of this exercise is to learn how to read and monitor the proximity value from the APDS9960 sensor.

APDS9960 is an advance sensor offering digital proximity, ambient light, RGB and gesture sensor in a very small package. amazing, right? The advance integrated IR LED and driver on the sensor, allows it to measure proximity (up to a few centimeters) with 8-bit resolution (value: 0-255). Below is an illustration of IR LED acts as proximity sensor.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight.gif" width="500"></a></p>

The built-in UV and IR blocking filters, allows APDS9960 to sense ambient light and RGB color. While, with four separate diodes sensitive to different directions and ambient light rejectino, allows it to sense gesture.

APDS9960 communication protocol is I2C. Therefore, we can interface it to ESP32 using I2C, to acquire its available measurement.

There is 1x APDS9960 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x39`**. The arrow is pointing towards gesture sensing **`UP`** direction.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-a.png" width="400"></a></p>

## Install Adafruit APDS9960 Library
Let's use [Adafruit_APDS9960](https://github.com/adafruit/Adafruit_APDS9960) library, to easily program the ESP32 to read the proximity value from the APDS9960 sensor. Following the steps below:
1. On the Arduino IDE, go to the Library Manager.
2. Search for **`adafruit apds9960`**.
3. Look for **Adafruit APDS9960 Library** by Adafruit, click the **INSTALL** button and wait until the installation process is done and the status on the library is *`1.2.x installed`*.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-b.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

## Complete Sketch
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


You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32. Once done uploading open the Serial Monitor and try to hover our hands up and down above the sensor. By observation, we can see on the Serial Monitor a proximity in an 8-bit chaning based on up and down of our hand. The closer the object, the higher the proximity value (maximum value: 255).

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/
myinvent/hibiscus-sense/raw/main/references/image-exercise-eight-c.gif" width="600"></a></p>

## Further Experiment
You can adjust the sensitivity threshold for proximity detection, using if statement to control actuators or use for counting purposes.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>