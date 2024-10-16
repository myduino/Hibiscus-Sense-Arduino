/*
 * Hibiscus Sense - Exercise 15 IoT using Favoriot MQTTS Protocol with Remote Procedure Call (RPC)
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 4 summary execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Initialized MQTT connection to Favoriot MQTT broker
 * 3. Data Acquisition - Read data from the sensors
 * 4. Data Ingestion - Send data to Favoriot's data stream using secure MQTT protocol
 *
 * Select the board as ESP32 Dev Module before compiling the sketch
 * (example) Go to menu, Tools > Board > esp32 > ESP32 Dev Module
 *
 * Favoriot's Secure Certificate Validity Expires On:
 * Saturday, 26 April 2025 at 08:54:18
 * 
 */

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

Adafruit_NeoPixel rgb(1, 16);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

unsigned long lastMillisUpdateInternval = 0;
unsigned long lastMillisDataInterval = 0;

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

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);

  bool ledBlue = doc.containsKey("ledBlue");
  bool ledRGB = doc.containsKey("ledRGB");

  if (ledBlue){
    int value = doc["ledBlue"];
    pinMode(2, OUTPUT); digitalWrite(2, value);
  }
  
  if (ledRGB){
    int value = doc["ledRGB"];
    rgb.setPixelColor(0, rgb.Color(value, value, value)); rgb.show();
  }
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
  Serial.println("Subscribe to: " + String(deviceAccessToken) + String(rpcTopic));

  mqtt.subscribe(String(deviceAccessToken) + String(statusTopic));
  mqtt.subscribe(String(deviceAccessToken) + String(rpcTopic));
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
  float altitude = bme.readAltitude(1015); // based on https://aqicn.org/
  mpu.getEvent(&a, &g, &temp);
  float accx = a.acceleration.x;
  float accy = a.acceleration.y;
  float accz = a.acceleration.z;
  float gyrx = g.gyro.x;
  float gyry = g.gyro.y;
  float gyrz = g.gyro.z;

  if (millis() - lastMillisDataInternval > 5000) {
    lastMillisDataInternval = millis();

    Serial.println("Proximity: " + String(proximity));
    Serial.println("Relative Humidity: " + String(humidity) + " %RH");
    Serial.println("Approx. Altitude: " + String(altitude) + " m");
    Serial.println("Barometric Pressure: " + String(barometer) + " hPa");
    Serial.println("Ambient Temperature: " + String(temperature) + " °C");
    Serial.println("Acceleration X:" + String(accx) + ", Y:" + String(accy) + ", Z:" + String(accz) + " m/s^2");
    Serial.println("Rotation X:" + String(gyrx) + ", Y:" + String(gyroy) + ", Z:" + String(gyroz) + " rad/s");
    Serial.println("=============================================");
  }

  // STEP 4: Data Ingestion - Send data to Favoriot's data stream using secure MQTT connection
  // Interval 15 seconds
  if (millis() - lastMillisUpdateInternval > 15000) {
    lastMillisUpdateInternval = millis();

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
}
