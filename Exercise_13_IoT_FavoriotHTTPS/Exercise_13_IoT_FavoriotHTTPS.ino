/*
 * Hibiscus Sense - Exercise 13 IoT using Favoriot HTTPS
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 3 execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Data Acquisition - Read data from the sensors
 * 3. Data Ingestion - Send data to Favoriot's data stream using HTTPS
 *
 * Please select ESP32 Boards before compiling the sketch
 * (example) Go to menu, Tools > Board > ESP32 Arduino
 *
 * Favoriot's HTTP Secure Certificate Validity Expires On:
 * Saturday, 27 May 2023 at 14:17:12
 * 
 */

#include <WiFi.h>
#include <HTTPClient.h>
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

const char ssid[] = "YourWiFiSSID";
const char pass[] = "YourWiFiPassword";
const char device_developer_id[] = "YourDeviceDeveloperId";
const char device_access_token[] = "YourDeviceAccessToken";

long previousMillis = 0;

void setup() {

  Serial.begin(9600);

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

  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

}

void loop() {

  if(millis() - previousMillis > 10000){

    previousMillis = millis();
    
    String json = "{\"device_developer_id\":\"" + String(device_developer_id) + "\",\"data\":{";
    
    json += "\"proximity\":\"" + String(apds.readProximity()) + "\",";
    json += "\"altitude\":\"" + String(bme.readAltitude(1013.25)) + "\",";
    json += "\"barometer\":\"" + String(bme.readPressure()/100.00) + "\",";
    json += "\"humidity\":\"" + String(bme.readHumidity()) + "\",";
    json += "\"temperature\":\"" + String(bme.readTemperature()) + "\",";
    
    mpu.getEvent(&a,&g,&temp);
    
    json += "\"accx\":\"" + String(a.acceleration.x) + "\",";
    json += "\"accy\":\"" + String(a.acceleration.y) + "\",";
    json += "\"accz\":\"" + String(a.acceleration.z) + "\",";
    json += "\"gyrox\":\"" + String(g.gyro.x) + "\",";
    json += "\"gyroy\":\"" + String(g.gyro.y) + "\",";
    json += "\"gyroz\":\"" + String(g.gyro.z) + "\"";
    
    json += "}}";

    WiFiClientSecure *client = new WiFiClientSecure;

    if(client) {
      client -> setCACert(FavoriotCA);
      {
        HTTPClient https;
      
        https.begin(*client, "https://apiv2.favoriot.com/v2/streams");
      
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Apikey", device_access_token);
        
        int httpCode = https.POST(json);
      
        if(httpCode > 0){
          Serial.print("> HTTPS Request: ");
          
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
      Serial.println("Unable to create client");
      Serial.println();
    }
  }
}
