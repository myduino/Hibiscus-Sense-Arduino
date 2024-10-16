/*
 * Hibiscus Sense - Exercise 12 IoT using Blynk
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 3 summary execution steps:
 * 1. Initialized Wi-Fi conectivity and Blynk Authentication
 * 2. Data Acquisition - Read data from the sensors
 * 3. Data Ingestion - Send data to Blynk's data stream
 *
 * Install Blynk library before using the sketch.
 * 
 * Select the board as ESP32 Dev Module before compiling the sketch
 * (example) Go to menu, Tools > Board > esp32 > ESP32 Dev Module
 * 
 */

#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_BME280.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourWiFiSSID";
char password[] = "YourWiFiPassword";

Adafruit_BME280 bme;

long previousMillis = 0;

BLYNK_WRITE(V2){
  int value = param.asInt();

  pinMode(2, OUTPUT);
  digitalWrite(2, value);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  if (!bme.begin()){
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }

  // STEP 1: Initialized Wi-Fi conectivity and Blynk Authentication
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();

  // Interval 1 seconds
  if(millis() - previousMillis > 1000){
    previousMillis = millis();
    
    // STEP 2: Data Acquisition - Read data from the sensors
    float humidity = bme.readHumidity();
    float temperature = bme.readTemperature();

    Serial.println("Humidity: " + String(humidity) + " %RH");
    Serial.println("Temperature: " + String(temperature) + " °C");

    Serial.println("=============================================");

    // STEP 3: Data Ingestion - Send data to Blynk's data stream using HTTPS
    Blynk.virtualWrite(V0, humidity);
    Blynk.virtualWrite(V1, temperature);

  }
}