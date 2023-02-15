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

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>