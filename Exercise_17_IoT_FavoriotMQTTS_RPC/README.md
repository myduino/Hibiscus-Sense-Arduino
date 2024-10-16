# Exercise 14: IoT Application using Favoriot (MQTTS Protocol)

This exercise aims to learn how to send data to the Favoriot IoT platform using a secure MQTT protocol.

This exercise is a continuation from Exercise 13, therefore device, dashboard and rule on Favoriot remain the same, the only protocol being used by ESP32 to connect to the Favoriot platform is to change to MQTT.

## Extra Information

You can get more information about Favoriot CAcertificate using MQTTS protocol from the link here: 
https://www.favoriot.com/mqtt-for-embedded-devices-now-supported-by-favoriot/

## Sending Data to Favoriot using secure MQTT protocol

Let's sending the Hibiscus Sense sensor's data to the Favoriot platform.

1. Open the sketch on Arduino IDE.

### Arduino Sketch

```cpp
#include <WiFi.h>
#include <MQTT.h>
#include <NetworkClientSecure.h>
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

// https://meteologix.com/my/observations/pressure-qnh.html
float hPaSeaLevel = 1015.00;

unsigned long lastMillis = 0;

NetworkClientSecure client;
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

  client.setCACert(rootCACertificate);

  mqtt.begin("mqtt.favoriot.com", 8883, client);
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
  // Check Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  // Check MQTT connection
  if (!mqtt.connected()) {
    connectToFavoriotMQTT();
  }

  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  // STEP 3: Data Acquisition - Read data from the sensors
    int proximity = apds.readProximity();
    float humidity = bme.readHumidity();
    float temperature = bme.readTemperature();
    float barometer = bme.readPressure() / 100.00;
    float altitude = bme.readAltitude(hPaSeaLevel);
    mpu.getEvent(&a, &g, &temp);
    float accx = a.acceleration.x;
    float accy = a.acceleration.y;
    float accz = a.acceleration.z;
    float gyrx = g.gyro.x;
    float gyry = g.gyro.y;
    float gyrz = g.gyro.z;

    Serial.print("Proximity: ");
    Serial.println(proximity);

    Serial.print("Relative Humidity: ");
    Serial.print(humidity);
    Serial.println(" %RH");

    Serial.print("Approx. Altitude: ");
    Serial.print(altitude);
    Serial.println(" m");

    Serial.print("Barometric Pressure: ");
    Serial.print(barometer);
    Serial.println(" Pa");

    Serial.print("Ambient Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Acceleration X:");
    Serial.print(accx);
    Serial.print(", Y:");
    Serial.print(accy);
    Serial.print(", Z:");
    Serial.print(accz);
    Serial.println(" m/s^2");

    Serial.print("Rotation X:");
    Serial.print(gyrx);
    Serial.print(", Y:");
    Serial.print(gyry);
    Serial.print(", Z:");
    Serial.print(gyrz);
    Serial.println(" rad/s");

  // STEP 4: Data Ingestion - Send data to Favoriot's data stream using secure MQTT connection
  // Interval 15 seconds
  if (millis() - lastMillis > 15000) {
    lastMillis = millis();

    String favoriotJson = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    favoriotJson += "\"proximity\":\"" + String(proximity) + "\",";
    favoriotJson += "\"humidity\":\"" + String(humidity) + "\",";
    favoriotJson += "\"altitude\":\"" + String(altitude) + "\",";
    favoriotJson += "\"barometer\":\"" + String(barometer) + "\",";
    favoriotJson += "\"temperature\":\"" + String(temperature) + "\",";
    favoriotJson += "\"accx\":\"" + String(accx) + "\",";
    favoriotJson += "\"accy\":\"" + String(accy) + "\",";
    favoriotJson += "\"accz\":\"" + String(accz) + "\",";
    favoriotJson += "\"gyrox\":\"" + String(gyrx) + "\",";
    favoriotJson += "\"gyroy\":\"" + String(gyry) + "\",";
    favoriotJson += "\"gyroz\":\"" + String(gyrz) + "\"";
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

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/favoriot-mqtts-serial-monitor.png" width="800"></a></p>

Now, you can monitor the data on Favoriot's Data Stream.

On the Favoriot platform, go to menu and click **Data Stream** to show the list of data streaming from the Hibiscus Sense.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/favoriot-data-stream.gif" width="800"></a></p>

Congratulations, you have completed this exercise and gain hands-on experience on how send data to the Favoriot IoT platform using secure MQTT protocol.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>