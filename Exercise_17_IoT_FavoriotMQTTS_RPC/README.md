# Exercise 17: IoT Application using Favoriot (MQTTS Protocol) with Remote Procedure Call (RPC)

This exercise aims to learn how to send data to the Favoriot IoT platform using a secure MQTT protocol.

This exercise is an extension of Exercise 14, therefore device, dashboard and rule on Favoriot remain the same. On the dashboard you need to add switch and sliders.

## Extra Information

You can get more information about Favoriot CAcertificate using MQTTS protocol from the link here: 
https://www.favoriot.com/mqtt-for-embedded-devices-now-supported-by-favoriot/

## Sending Data to Favoriot using secure MQTT protocol

Let's send the Hibiscus Sense sensor's data to the Favoriot' Data Stream and monitor the data and control the actuators from the Favoriot's Dashboard.

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
#include <ArduinoJson.h>
#include "FavoriotCA.h"

const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";
const char publishTopic[] = "/v2/streams";
const char statusTopic[] = "/v2/streams/status";
const char rpcTopic[] = "/v2/rpc";

Adafruit_NeoPixel rgb(1, 16, NEO_GRB + NEO_KHZ800);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

unsigned long lastMillisUpdateInternval = 0;
unsigned long lastMillisDataInterval = 0;

NetworkClientSecure client;
MQTTClient mqtt(4096);

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi AP '" + String(ssid) + "' ...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");
}

void connectToFavoriotMQTT() {
  Serial.print("Connecting to Favoriot MQTT Broker ...");

  client.setCACert(rootCACertificate);

  mqtt.begin("mqtt.favoriot.com", 8883, client);
  mqtt.onMessage(rpcMessageReceived);

  String uniqueString = String(ssid) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];

  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);

  while (!mqtt.connect(uniqueClientID, deviceAccessToken, deviceAccessToken)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  Serial.println("Subscribe to: " + String(deviceAccessToken) + String(statusTopic));
  Serial.println("Subscribe to: " + String(deviceAccessToken) + String(rpcTopic));

  // Subscribe to /v2/streams/status
  mqtt.subscribe(String(deviceAccessToken) + String(statusTopic));
  // Subscribe to /v2/rpc
  mqtt.subscribe(String(deviceAccessToken) + String(rpcTopic));
  Serial.println();
}

// Function to handle RPC message
void rpcMessageReceived(String &topic, String &payload) {
  Serial.println("Incoming Status - Topic: " + topic + ", Payload: " + payload);
  Serial.println();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);

  bool ledBlue = doc.containsKey("ledBlue");
  bool ledRedRGB = doc.containsKey("ledRedRGB");
  bool ledRGB = doc.containsKey("ledRGB");

  if (ledBlue) {
    int value = doc["ledBlue"];
    digitalWrite(2, value);
  }

  if (ledRedRGB) {
    int value = doc["ledRedRGB"];
    rgb.setPixelColor(0, rgb.Color(value, 0, 0));
    rgb.show();
  }

  if (ledRGB) {
    int valueRed = doc["ledRGB"]["r"];
    int valueGreen = doc["ledRGB"]["g"];
    int valueBlue = doc["ledRGB"]["b"];
    rgb.setPixelColor(0, rgb.Color(valueRed, valueGreen, valueBlue));
    rgb.show();
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize Blue LED
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  // Initialize RGB LED
  rgb.begin();
  rgb.clear();

  // Initialize APDS9960 Sensor
  if (!apds.begin()) {
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  apds.enableProximity(true);

  // Initialize BME280 Sensor
  if (!bme.begin()) {
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }

  // Initialize MPU6050 Sensor
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
  float altitude = bme.readAltitude(1015);  // based on https://aqicn.org/
  mpu.getEvent(&a, &g, &temp);
  float accx = a.acceleration.x;
  float accy = a.acceleration.y;
  float accz = a.acceleration.z;
  float gyrx = g.gyro.x;
  float gyry = g.gyro.y;
  float gyrz = g.gyro.z;

  // Print data on Serial Monitor
  // Interval 5 seconds
  if (millis() - lastMillisDataInterval > 5000) {
    lastMillisDataInterval = millis();

    Serial.println("Proximity: " + String(proximity));
    Serial.println("Relative Humidity: " + String(humidity) + " %RH");
    Serial.println("Approx. Altitude: " + String(altitude) + " m");
    Serial.println("Barometric Pressure: " + String(barometer) + " hPa");
    Serial.println("Ambient Temperature: " + String(temperature) + " °C");
    Serial.println("Acceleration X: " + String(accx) + ", Y:" + String(accy) + ", Z:" + String(accz) + " m/s^2");
    Serial.println("Rotation X: " + String(gyrx) + ", Y:" + String(gyry) + ", Z:" + String(gyrz) + " rad/s");
    Serial.println();
  }

  // STEP 4: Data Ingestion - Send data to Favoriot's data stream using secure MQTT connection
  // Interval 15 seconds
  if (millis() - lastMillisUpdateInternval > 15000) {
    lastMillisUpdateInternval = millis();

    String json = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    json += "\"proximity\":\"" + String(proximity) + "\",";
    json += "\"humidity\":\"" + String(humidity) + "\",";
    json += "\"altitude\":\"" + String(altitude) + "\",";
    json += "\"barometer\":\"" + String(barometer) + "\",";
    json += "\"temperature\":\"" + String(temperature) + "\",";
    json += "\"accx\":\"" + String(accx) + "\",";
    json += "\"accy\":\"" + String(accy) + "\",";
    json += "\"accz\":\"" + String(accz) + "\",";
    json += "\"gyrox\":\"" + String(gyrx) + "\",";
    json += "\"gyroy\":\"" + String(gyry) + "\",";
    json += "\"gyroz\":\"" + String(gyrz) + "\"";
    json += "}}";

    Serial.println("\nSending data to Favoriot's Data Stream ...");

    Serial.println("Data to Publish: " + json);
    Serial.println("Publish to: " + String(deviceAccessToken) + String(publishTopic));

    mqtt.publish(String(deviceAccessToken) + String(publishTopic), json);

    Serial.println("======================================================");
    Serial.println();
  }
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

The program control the ESP32 to collect and print the sensor's data with interval time of 5 seconds and interval time of 15 seconds to send the data to Favoriot platform.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/favoriot-mqtts-serial-monitor.png" width="800"></a></p>

Now, you can monitor the data on Favoriot's Data Stream.

On the Favoriot platform, go to menu and click **Data Stream** to show the list of data streaming from the Hibiscus Sense.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/favoriot-data-stream.gif" width="800"></a></p>

Congratulations, you have completed this exercise and gain hands-on experience on how send data to the Favoriot IoT platform using secure MQTT protocol.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>
