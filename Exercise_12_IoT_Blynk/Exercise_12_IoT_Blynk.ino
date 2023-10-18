/*
 * Hibiscus Sense - Exercise 12 IoT using Blynk
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 3 execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Connect to the Blynk IoT platform
 * 3. Data Acquisition - Read data from the sensors
 * 4. Data Ingestion - Send data to Blynk's data stream using HTTPS
 *
 * Install Blynk library before using the sketch.
 * 
 * Please select ESP32 Boards before compiling the sketch
 * (example) Go to menu, Tools > Board > ESP32 Arduino
 * 
 */

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

Adafruit_NeoPixel rgb(1, 16);

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

sensors_event_t a, g, temp;

int R = 0, G = 0, B = 0;

long previousMillis = 0;

BLYNK_WRITE(V11){
  R = param[0].asInt();
  G = param[1].asInt();
  B = param[2].asInt();
}

void setup(){
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  if (!apds.begin()){
    Serial.println("Failed to find Hibiscus Sense APDS9960 chip");
  }

  apds.enableProximity(true);

  if (!bme.begin()){
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }

  if (!mpu.begin()){
    Serial.println("Failed to find Hibiscus Sense MPU6050 chip");
  }

  rgb.begin();
  rgb.show();
}

void loop(){

  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass);

    while(WiFi.status() != WL_CONNECTED);
  }
  
  Blynk.run();

  rgb.setPixelColor(0, R, G, B);
  rgb.show();

  if(millis() - previousMillis > 500){
    previousMillis = millis();

    Blynk.virtualWrite(V0, apds.readProximity());

    Blynk.virtualWrite(V1, bme.readAltitude(1013.25));
    Blynk.virtualWrite(V2, bme.readPressure()/1000.00);
    Blynk.virtualWrite(V3, bme.readHumidity());
    Blynk.virtualWrite(V4, bme.readTemperature());
  
    mpu.getEvent(&a, &g, &temp);
  
    Blynk.virtualWrite(V5, a.acceleration.x);
    Blynk.virtualWrite(V6, a.acceleration.y);
    Blynk.virtualWrite(V7, a.acceleration.z);
    Blynk.virtualWrite(V8, g.gyro.x);
    Blynk.virtualWrite(V9, g.gyro.y);
    Blynk.virtualWrite(V10, g.gyro.z);
  }
}
