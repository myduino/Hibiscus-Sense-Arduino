/*
 * Hibiscus Sense Example Sketch - APDS9960
 * 
 * There is 1x APDS9960, a proximity sensor.
 * The sensor sense proximity, gesture and rgb color.
 * This sensor is interfaced to the I2C of ESP32 microcontroller.
 * 
 * Therefore in the sketch,
 * we will use an Arduino library: Adafruit_APDS9960 from Adafruit, to monitor gesture direction.
 * 
 */

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
  // enable the gesture mode on APDS9960
  apds.enableGesture(true);
}

void loop() {
  // to acquire APDS9960 gesture direction,
  // we need to call apds.readGesture() function from apds instance.

  uint8_t gesture = apds.readGesture();

  if(gesture == APDS9960_DOWN) Serial.println("Gesture Direction: DOWN");
  if(gesture == APDS9960_UP) Serial.println("Gesture Direction: UP");
  if(gesture == APDS9960_LEFT) Serial.println("Gesture Direction: LEFT");
  if(gesture == APDS9960_RIGHT) Serial.println("Gesture Direction: RIGHT");
  
}
