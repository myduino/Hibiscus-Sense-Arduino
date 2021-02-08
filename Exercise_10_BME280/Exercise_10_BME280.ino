/*
 * Hibiscus Sense Example Sketch - BME280
 * 
 * There is 1x BME280, an environment sensor.
 * The sensor sense altitude, barometric pressure, humidity and temperature.
 * This sensor is interfaced to the I2C of ESP32 microcontroller.
 * 
 * Therefore in the sketch,
 * we will use an Arduino library: Adafruit_BME280 from Adafruit, to acquire BME280 data.
 * 
 */

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
