/*
 * Hibiscus Sense - Exercise 11 MPU6050
 * 
 * There is 1x MPU6050, 6-axis motion tracking and temperature sensor.
 * The sensor sense 3-axis accelerometer, the gravitational acceleration, 3-axis gyroscope, the rotational velocity and temperature.
 * This sensor is interfaced to the I2C of ESP32 microcontroller.
 * 
 * Therefore in the sketch,
 * we will use an Arduino library: Adafruit_MPU6050 from Adafruit, to acquire the accelerometer, gyroscope and temperature value.
 * 
 */

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
