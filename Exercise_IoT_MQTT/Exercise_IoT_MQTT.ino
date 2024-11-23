/*
 * Hibiscus Sense - Exercise IoT using MQTT
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 7 execution steps:
 * 1. Initialized Actuators, Input, and Sensors
 * 2. Connect Wi-Fi AP
 * 3. Connect to MQTT Broker
 * 4. Data Control - Wait from the subscription MQTT topic
 * 5. Data Acquisition - Read data from the sensors
 * 6. Data Ingestion - Send data to publish MQTT topic
 * 7. Data Trigger - Send trigger to MQTT topic
 *
 * Please select ESP32 Boards before compiling the sketch
 * (example) Go to menu, Tools > Board > ESP32 Arduino
 *
 * Before compiling the sketch make sure you have installed
 * all necessary libraries required by this sketch.
 * 
 */

// Include necessary libraries
#include <Adafruit_Sensor.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>

// Define Wi-Fi and MQTT configurations
#define WIFI_SSID             "YourWiFiSSID"
#define WIFI_PASSWORD         "YourWiFiPassword"
#define MQTT_HOST             "MQTTBrokerDNSorIP"
#define MQTT_PREFIX_TOPIC     "hibiscus-sense/"
#define MQTT_UNIQUE_TOPIC     "YourPhoneNumber"
#define MQTT_PUBLISH_TOPIC    "/data"
#define MQTT_TRIGGER_TOPIC    "/trigger"
#define MQTT_SUBSCRIBE_TOPIC  "/control"
#define MQTT_RGB_TOPIC        "/rgb"
#define MQTT_LED_TOPIC        "/led"

#define SEALEVELPRESSURE_HPA (1008) // Average for Malaysia based on https://meteologix.com/

// Initialize sensors and sensor event variables
Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

// Initialize RGB LED
Adafruit_NeoPixel rgb(1, 16, NEO_GRB + NEO_KHZ800);

// Define LED-related variables
const int ledPin = 2;

// Define button-related variables
const int buttonPin = 0;
volatile bool buttonPressed = false;
int toggleValue = 0;

// Initialize Wi-Fi client and MQTT client
WiFiClient net;
MQTTClient mqtt(1024);

unsigned long lastMillis, sendMillis = 0;

// Interrupt handler for button press
void IRAM_ATTR handleButtonPress() {
  buttonPressed = true;
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi AP '" + String(WIFI_SSID) + "' ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" connected!");
}

// Function to handle MQTT messages
void messageReceived(String &topic, String &payload) {
  Serial.println("MQTT SUBSCRIPTION ...");
  Serial.println("Subscribe Message Received: " + payload);

  if(topic == String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_RGB_TOPIC)){

    // Extract RGB values from the payload
    int commaIndex = payload.indexOf(", ");
    int secondCommaIndex = payload.indexOf(", ", commaIndex+1);
    int thirdCommaIndex = payload.indexOf(", ", secondCommaIndex+1);

    int red = payload.substring(payload.indexOf("rgb(")+4, commaIndex).toInt();
    int green = payload.substring(commaIndex+1, secondCommaIndex).toFloat();
    int blue = payload.substring(secondCommaIndex+1, thirdCommaIndex).toFloat();

    // Set the RGB LED color
    Serial.print("CONTROL RGB ... ");
    rgb.setPixelColor(0, rgb.Color(red, green, blue));
    rgb.show();
    Serial.println("OK");
  }

  if(topic == String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_LED_TOPIC)){
    // Adjust the LED brightness based on the payload
    Serial.print("CONTROL LED ... ");
    analogWrite(ledPin, 255 - payload.toInt());
    Serial.println("OK");
  }

  Serial.println();
  
}

// Function to connect to MQTT broker
void connectToMqttBroker(){
  Serial.print("Connecting to MQTT broker '" + String(MQTT_HOST) + "' ...");
  
  mqtt.begin(MQTT_HOST, net);
  mqtt.onMessage(messageReceived);

  // Generate a unique client ID for MQTT connection
  String uniqueString = String(WIFI_SSID) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];
  
  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);
  
  while (!mqtt.connect(uniqueClientID, "admin", "password")) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  // Subscribe to MQTT topics for control
  Serial.println("Subscribe to MQTT topic: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_RGB_TOPIC));
  Serial.println("Subscribe to MQTT topic: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_LED_TOPIC));
  
  mqtt.subscribe(String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_RGB_TOPIC));
  mqtt.subscribe(String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC) + String(MQTT_LED_TOPIC));
}

void setup() {

  Serial.begin(115200);

  Serial.println("HIBISCUS SENSE");
  Serial.println();

  Serial.println("Initializing Actuators:");

  // Initialize and configure LED
  Serial.print("1. LED ... ");
  pinMode(ledPin, OUTPUT);
  Serial.println("OK");

  // Initialize RGB LED
  Serial.print("2. RGB LED ... ");
  rgb.begin();
  rgb.show();
  Serial.println("OK");
  Serial.println();

  Serial.println("Initializing Input:");
  // Initialize push button
  Serial.print("1. Pushbutton ... ");
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
  Serial.println("OK");
  Serial.println();

  Serial.println("Initializing Sensors:");
  
  // Initialize and configure APDS9960 sensor
  Serial.print("1. APDS9960 ... ");
  if (!apds.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");
  }

  // Initialize and configure BME280 sensor
  Serial.print("2. BME280 ... ");
  if (!bme.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");
  }
  
  // Initialize and configure MPU6050 sensor
  Serial.print("3. MPU6050 ... ");
  if (!mpu.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");    
  }
  Serial.println();

  // Enable proximity sensing
  apds.enableProximity(true);

  // Set sensor ranges and bandwidth
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Connect to Wi-Fi and MQTT broker
  connectToWiFi();
  connectToMqttBroker();

  Serial.println();
}

void loop() {
  // Maintain MQTT connection
  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  // Reconnect to Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  // Reconnect to MQTT broker if disconnected
  if (!mqtt.connected()) {
    connectToMqttBroker();
  }

  // Handle button presses
  if (buttonPressed) {
    toggleValue = !toggleValue;

    Serial.println("MQTT PUBLISHER ...");
    Serial.println("Publish Trigger: " + String(toggleValue));
    Serial.println();
    mqtt.publish(String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_TRIGGER_TOPIC), String(toggleValue));
    
    buttonPressed = false;
  }

  // Read sensor data and print periodically
  uint8_t proximity = apds.readProximity();

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float barometer = bme.readPressure() / 100.0F;

  mpu.getEvent(&a, &g, &temp);

  float x_axis = a.acceleration.x;
  float y_axis = a.acceleration.y;
  float z_axis = a.acceleration.z;

  float x_gyro = g.gyro.x;
  float y_gyro = g.gyro.y;
  float z_gyro = g.gyro.z;

  if (millis() - lastMillis > 5000) {
    lastMillis = millis();

    // Print sensor data
    Serial.println("SENSORS MEASUREMENT ...");
    Serial.println("1. Proximity: " + String(proximity));
    Serial.println("2. Temperature: " + String(temperature) + " °C");
    Serial.println("3. Humidity: " + String(humidity) + " %RH");
    Serial.println("4. Approx. Altitude: " + String(altitude) + " m");
    Serial.println("5. Barometer: " + String(barometer) + " hPa");
    Serial.println("6. Accelerometer X: " + String(x_axis) + ", Y: " + String(y_axis) + ", Z: " + String(z_axis) + " m/s^2");
    Serial.println("7. Gyrometer X: " + String(x_gyro) + ", Y: " + String(y_gyro) + ", Z: " + String(z_gyro) + " rad/s");
    
    Serial.println();
  }

  // Publish sensor data to MQTT at regular intervals
  if (millis() - sendMillis > 10000) {
    sendMillis = millis();

    // Create a JSON-formatted data string
    String dataInJson = "{";
    dataInJson += "\"proximity\":" + String(proximity) + ",";
    dataInJson += "\"temperature\":" + String(temperature) + ",";
    dataInJson += "\"humidity\":" + String(humidity) + ",";
    dataInJson += "\"barometer\":" + String(barometer) + ",";
    dataInJson += "\"altitude\":" + String(altitude) + ",";
    dataInJson += "\"x_axis\":" + String(x_axis) + ",";
    dataInJson += "\"y_axis\":" + String(y_axis) + ",";
    dataInJson += "\"z_axis\":" + String(z_axis) + ",";
    dataInJson += "\"x_gyro\":" + String(x_gyro) + ",";
    dataInJson += "\"y_gyro\":" + String(y_gyro) + ",";
    dataInJson += "\"z_gyro\":" + String(z_gyro);
    
    dataInJson += "}";

    // Print and publish the data
    Serial.println("MQTT PUBLISHER ...");
    Serial.println("Data to Publish: " + dataInJson);
    Serial.println("Length of Data: " + String(dataInJson.length()));
    Serial.println("Publish to MQTT topic: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_PUBLISH_TOPIC));
    Serial.println();
    
    mqtt.publish(String(MQTT_PREFIX_TOPIC) + String(MQTT_UNIQUE_TOPIC) + String(MQTT_PUBLISH_TOPIC), dataInJson);
  }
}