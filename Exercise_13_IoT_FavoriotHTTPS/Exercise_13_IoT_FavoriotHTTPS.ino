/*
 * Hibiscus Sense - Exercise 13 IoT using Favoriot HTTPS Protocol
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 3 summary execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Data Acquisition - Read data from the sensors
 * 3. Data Ingestion - Send data to Favoriot's data stream using secure HTTP protocol
 *
 * Select the board as ESP32 Dev Module before compiling the sketch
 * (example) Go to menu, Tools > Board > esp32 > ESP32 Dev Module
 *
 * Favoriot's Secure Certificate Validity Expires On:
 * Saturday, 26 April 2025 at 08:54:18
 * 
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include "FavoriotCA.h"

Adafruit_NeoPixel rgb(1, 16);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";

long previousMillis = 0;

void setup() {

  Serial.begin(115200);

  rgb.begin();
  rgb.show();

  if(!apds.begin()){
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  apds.enableProximity(true);

  if (!bme.begin()){
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }

  if (!mpu.begin()){
    Serial.println("Failed to find Hibiscus Sense MPU6050 chip");
  }

  // STEP 1: Initialized Wi-Fi conectivity
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

}

void loop() {
  // STEP 2: Data Acquisition - Read data from the sensors
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

  // STEP 3: Data Ingestion - Send data to Favoriot's data stream using secure HTTP connection
  // Interval 15 seconds
  if(millis() - previousMillis > 15000){
    previousMillis = millis();
    
    String json = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    
    json += "\"proximity\":\"" + String(apds.readProximity()) + "\",";
    json += "\"humidity\":\"" + String(bme.readHumidity()) + "\",";
    json += "\"altitude\":\"" + String(bme.readAltitude(1013.25)) + "\",";
    json += "\"barometer\":\"" + String(bme.readPressure()/100.00) + "\",";
    json += "\"temperature\":\"" + String(bme.readTemperature()) + "\",";
    
    mpu.getEvent(&a,&g,&temp);
    
    json += "\"accx\":\"" + String(a.acceleration.x) + "\",";
    json += "\"accy\":\"" + String(a.acceleration.y) + "\",";
    json += "\"accz\":\"" + String(a.acceleration.z) + "\",";
    json += "\"gyrox\":\"" + String(g.gyro.x) + "\",";
    json += "\"gyroy\":\"" + String(g.gyro.y) + "\",";
    json += "\"gyroz\":\"" + String(g.gyro.z) + "\"";
    
    json += "}}";

    Serial.println("\nSending data to Favoriot's Data Stream ...");

    NetworkClientSecure *client = new NetworkClientSecure;

    if(client) {
      client -> setCACert(FavoriotCA);
      {
        HTTPClient https;
      
        https.begin(*client, "https://apiv2.favoriot.com/v2/streams");
      
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Apikey", deviceAccessToken);
        
        int httpCode = https.POST(json);
      
        if(httpCode > 0){
          Serial.print("HTTPS Request: ");
          
          httpCode == 201 ? Serial.print("Success, ") : Serial.print("Error, ");
          Serial.println(https.getString());
        }
        else{
          Serial.println("> HTTPS Request Connection Error!");
        }
      
        https.end();
        Serial.println();
      }

      delete client;
    }
    else{
      Serial.println("Unable to create secure client connection!");
      Serial.println();
    }
  }

  Serial.println("=============================================");
  // delay(3000);
}
