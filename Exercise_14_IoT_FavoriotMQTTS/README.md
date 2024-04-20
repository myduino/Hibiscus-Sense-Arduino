# Exercise 14: IoT Application using Favoriot (MQTTS Protocol)

The aim of this exercise is to learn how to send data to the Favoriot IoT platform using secure MQTT connection.

This exercise is continuation from Exercise 13, therefore device, dashboard and rule on Favoriot remain same, only protocol being used by ESP32 to connect to Favoriot platform is change to MQTT.

## Sending Data to Favoriot using secure MQTT connection

Let's sending the Hibiscus Sense sensor's data to Favoriot platform.

1. Open the sketch on Arduino IDE.

### Arduino Sketch

```cpp
#include <WiFiClientSecure.h>
#include <MQTT.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include "FavoriotCA.h"

const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";
const char publishTopic[] = "/v2/streams";
const char statusTopic[] = "/v2/streams/status";

Adafruit_NeoPixel rgb(1, 16);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

unsigned long lastMillis = 0;

WiFiClientSecure net;
MQTTClient mqtt(4096);

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi '" + String(ssid) + "' ...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming Status: " + payload);
  Serial.println();
}

void connectToFavoriotMQTT() {
  Serial.print("Connecting to Favoriot MQTT ...");

  net.setCACert(rootCACertificate);

  mqtt.begin("mqtt.favoriot.com", 8883, net);
  mqtt.onMessage(messageReceived);

  String uniqueString = String(ssid) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];

  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);

  while (!mqtt.connect(uniqueClientID, deviceAccessToken, deviceAccessToken)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  Serial.println("Subscribe to: " + String(deviceAccessToken) + String(statusTopic));

  mqtt.subscribe(String(deviceAccessToken) + String(statusTopic));
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  rgb.begin();
  rgb.show();

  if (!apds.begin()) {
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  apds.enableProximity(true);

  if (!bme.begin()) {
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find Hibiscus Sense MPU6050 chip");
  }

  Serial.println();

  // STEP 1: Initialized Wi-Fi conectivity
  connectToWiFi();
  // STEP 2: Initialized MQTT connection to Favoriot MQTT broker
  connectToFavoriotMQTT();
}

void loop() {
  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (!mqtt.connected()) {
    connectToFavoriotMQTT();
  }

  // STEP 3: Data Acquisition - Read data from the sensors
  Serial.print("Proximity: ");
  Serial.println(apds.readProximity());

  Serial.print("Relative Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %RH");

  Serial.print("Approx. Altitude: ");
  Serial.print(bme.readAltitude(1013.25));
  Serial.println(" m");

  Serial.print("Barometric Pressure: ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");

  Serial.print("Ambient Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  mpu.getEvent(&a, &g, &temp);

  Serial.print("Acceleration X:");
  Serial.print(a.acceleration.x);
  Serial.print(", Y:");
  Serial.print(a.acceleration.y);
  Serial.print(", Z:");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X:");
  Serial.print(g.gyro.x);
  Serial.print(", Y:");
  Serial.print(g.gyro.y);
  Serial.print(", Z:");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  // STEP 4: Data Ingestion - Send data to Favoriot's data stream using secure MQTT connection
  // Interval 15 seconds
  if (millis() - lastMillis > 15000) {
    lastMillis = millis();

    String favoriotJson = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    
    favoriotJson += "\"proximity\":\"" + String(apds.readProximity()) + "\",";
    favoriotJson += "\"humidity\":\"" + String(bme.readHumidity()) + "\",";
    favoriotJson += "\"altitude\":\"" + String(bme.readAltitude(1013.25)) + "\",";
    favoriotJson += "\"barometer\":\"" + String(bme.readPressure()/100.00) + "\",";
    favoriotJson += "\"temperature\":\"" + String(bme.readTemperature()) + "\",";
    
    mpu.getEvent(&a,&g,&temp);
    
    favoriotJson += "\"accx\":\"" + String(a.acceleration.x) + "\",";
    favoriotJson += "\"accy\":\"" + String(a.acceleration.y) + "\",";
    favoriotJson += "\"accz\":\"" + String(a.acceleration.z) + "\",";
    favoriotJson += "\"gyrox\":\"" + String(g.gyro.x) + "\",";
    favoriotJson += "\"gyroy\":\"" + String(g.gyro.y) + "\",";
    favoriotJson += "\"gyroz\":\"" + String(g.gyro.z) + "\"";
    
    favoriotJson += "}}";

    Serial.println("\nSending data to Favoriot's Data Stream ...");

    Serial.println("Data to Publish: " + favoriotJson);
    Serial.println("Publish to: " + String(deviceAccessToken) + String(publishTopic));

    mqtt.publish(String(deviceAccessToken) + String(publishTopic), favoriotJson);
  }

  Serial.println("=============================================");
  delay(3000);
}

```

2. Replace these lines variable into your own details.

```cpp
const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";
```

3. Upload the sketch into the ESP32. Once done uploading open the Serial Monitor and observe the process and output on the Serial Monitor.

The program control the ESP32 to read and print the sensor's data with interval 3 seconds and interval 15 seconds send the data to Favoriot platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-mqtts-serial-monitor.png" width="800"></a></p>

Now, you can monitor the data on Favoriot's Data Stream.

On the Favoriot platform, go to menu and click **Data Stream** to show the list of data streaming from the Hibiscus Sense.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-data-stream.gif" width="800"></a></p>

Congratulations, you have completed this exercise and gain hands-on experience on how send data to the Favoriot IoT platform using secure MQTT connection.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>