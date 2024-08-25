/*
 * Hibiscus Sense - Exercise 16 IoT using Favoriot Websocket Secure Protocol
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 4 summary execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Initialized Websocket connection to Favoriot
 * 3. Data Acquisition - Read data from the sensors
 * 4. Data Ingestion - Send data to Favoriot's data stream using secure Websocket protocol
 *
 * Select the board as ESP32 Dev Module before compiling the sketch
 * (example) Go to menu, Tools > Board > esp32 > ESP32 Dev Module
 * 
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "FavoriotCA.h"

WebSocketsClient webSocket;

Adafruit_NeoPixel rgb(1, 16);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

// https://meteologix.com/my/observations/pressure-qnh.html
float hPaSeaLevel = 1015.00;

long previousMillis = 0;

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Favoriot WebSocket Server Details
const char* favoriotHost = "io.favoriot.com";
uint16_t favoriotPort = 443;
const char* favoriotProtocol = "/socket.io/?transport=websocket";
const char* favoriotEventName = "v2/streams";
const char* favoriotApiKey = "YOUR_API_KEY";

// Favoriot Device Details
const char* favoriotDeviceDeveloperId = "YOUR_DEVICE_DEVELOPER_ID";

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi '" + String(ssid) + "' ...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
			Serial.printf("Websocket disconnected!\n");
			break;
		case WStype_CONNECTED:
			Serial.println("connected!");
			break;
		case WStype_TEXT:
			Serial.printf("Websocket response: %s\n", payload);
			break;
		case WStype_BIN:
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
	}
}

void setup() {
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();

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

	// STEP 2: Initialized Websocket connection to Favoriot
  Serial.print("Connecting to " + String(favoriotHost) + " ... ");
  webSocket.beginSSL(favoriotHost, favoriotPort, favoriotProtocol);

	// Websocket event handler
	webSocket.onEvent(webSocketEvent);

	// Websocket reconnect again if connection has failed
	webSocket.setReconnectInterval(5000);
}

void loop() {
  // Check Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

	webSocket.loop();

  // Interval 15 seconds
  if (millis() - previousMillis > 30000) {
    previousMillis = millis();

    // STEP 3: Data Acquisition - Read data from the sensors
    mpu.getEvent(&a, &g, &temp);

    uint8_t proximity = apds.readProximity();
    float humidity = bme.readHumidity();
    float temperature = bme.readTemperature();
    float altitude = bme.readAltitude(hPaSeaLevel);
    float barometer = bme.readPressure();
    float accx = a.acceleration.x;
    float accy = a.acceleration.y;
    float accz = a.acceleration.z;
    float gyrox = g.gyro.x;
    float gyroy = g.gyro.y;
    float gyroz = g.gyro.z;

    Serial.println("\n==========================================================================================");
    
    Serial.print("Proximity: ");
    Serial.println(proximity);

    Serial.print("Relative Humidity: ");
    Serial.print(humidity);
    Serial.println(" %RH");

    Serial.print("Ambient Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Approx. Altitude: ");
    Serial.print(altitude);
    Serial.println(" m");

    Serial.print("Barometric Pressure: ");
    Serial.print(barometer);
    Serial.println(" Pa");

    Serial.print("Acceleration X:");
    Serial.print(accx);
    Serial.print(", Y:");
    Serial.print(accy);
    Serial.print(", Z:");
    Serial.print(accz);
    Serial.println(" m/s^2");

    Serial.print("Rotation X:");
    Serial.print(gyrox);
    Serial.print(", Y:");
    Serial.print(gyroy);
    Serial.print(", Z:");
    Serial.print(gyroz);
    Serial.println(" rad/s");

    JsonDocument doc;

    doc.add(favoriotEventName);

    JsonObject stream = doc.add<JsonObject>();
    stream["request"] = "push";
    stream["apikey"] = favoriotApiKey;

    JsonObject parameters = stream["parameters"].to<JsonObject>();
    parameters["device_developer_id"] = favoriotDeviceDeveloperId;

    JsonObject data = parameters["data"].to<JsonObject>();
    data["proximity"] = proximity;
    data["altitude"] = altitude;
    data["barometer"] = barometer;
    data["humidity"] = humidity;
    data["temperature"] = temperature;
    data["accx"] = accx;
    data["accy"] = accy;
    data["accz"] = accz;
    data["gyrox"] = gyrox;
    data["gyroy"] = gyroy;
    data["gyroz"] = gyroz;

    String outputJSON;
    serializeJson(doc, outputJSON);

    String outputSerial;
    serializeJsonPretty(doc, outputSerial);

    Serial.println("\nSending data to Favoriot's Data Stream ...");
    Serial.println("Data to Send: " + outputSerial);

    // Add message event code
    String payload = "42" + outputJSON;

    // STEP 4: Data Ingestion - Send data to Favoriot's data stream using secure Websocket connection
    webSocket.sendTXT(payload);

    Serial.println();
  }
}