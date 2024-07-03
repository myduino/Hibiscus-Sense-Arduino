# Exercise 09: Monitor Hand Gesture Direction using APDS9960

The aim of this exercise is to learn how to detect the hand gestures using the APDS9960 sensor.

In this exercise, we will use same APDS9960 from [Exercise 8](https://github.com/myduino/Hibiscus-Sense-Arduino#exercise-8-monitor-proximity-value-from-apds9960) with different application of sensing gesture direction, the sketch as follows:

## Complete Sketch

```cpp
// include the Adafruit_APDS9960 header file.
#include <Adafruit_APDS9960.h>

// instance of the Adafruit_APDS9960 class named as apds.
Adafruit_APDS9960 apds;

void setup() {
  // Initialize the serial communication with baud rate 9600bps.
  Serial.begin(115200);
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
```

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32. Once done uploading open the Serial Monitor. To try the gesture:
1. Activate the proximity by hovering our hands close as possible above the APDS9960.
2. Make gesture by hivering our hands into direction of UP, DOWN, RIGHT and LEFT.

We should see the direction on the Serial Monitor, as on the image below:

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-nine.gif" width="600"></a></p>

## Further Experiment
You can customize the behavior based on specific gestures (e.g., controlling an LED or buzzer) or combine gesture detection with other sensors or actuators for interactive projects.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>