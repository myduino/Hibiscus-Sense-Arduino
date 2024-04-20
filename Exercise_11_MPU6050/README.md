# Exercise 11: Monitor 6-Axis Motion Tracking using MPU6050

The aim of this exercise is to learn how to read and monitori 6-axis motion tracking using the MPU6050 sensor.

MPU6050 is a 6-axis motion tracking sensor by [InvenSense](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) to measure:
1. 3-axis accelerometer, the gravitational acceleration.
2. 3-axis gyroscope, the rotational velocity.
3. Ambient temperature.

There is 1x MPU6050 on Hibiscus Sense, as on the image below. The circuit is interfaced to **ESP32's I2C** (`SDA`: **GPIO21**, `SCL`: **GPIO22**) with the sensor I2C default address: **`0x68`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eleven.png" width="400"></a></p>

## Install Adafruit MPU6050 Library
Let's use [Adafruit_MPU6050](https://github.com/adafruit/Adafruit_MPU6050) library, to easily program the ESP32 to read the 6-axis motion tracking from the MPU6050 sensor. Following the steps below:
1. On the Arduino IDE, go to the Library Manager.
2. Search for **`adafruit mpu6050`**.
3. Look for **Adafruit MPU6050** by Adafruit, click the **INSTALL** button and wait until the installation process is done and the status on the library is *`2.2.x installed`*.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eleven-a.png" width="700"></a></p>

Once the library is successfully installed, we can start to write the sketch to monitor proximity value as below:

## Complete Sketch

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

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32. Once done uploading open the Serial Monitor and move around Hibiscus Sense. Then, you'll see latest value 3-axis accelerometer, 3-axis gyroscope and temperature.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-eleven.gif" width="600"></a></p>

# Further Experiment
You can combine the MPU6050 data with other sensors or actuators for more complex projects.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>