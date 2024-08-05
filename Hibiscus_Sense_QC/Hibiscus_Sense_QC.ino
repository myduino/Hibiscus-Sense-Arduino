// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <MQTT.h>
#include <Wire.h>

#define WIFI_SSID                 "Myduino Guest"
#define WIFI_PASSWORD             "MyduinoGuest"
#define MQTT_HOST                 "broker.hivemq.com"
#define MQTT_PUBLISH_TOPIC        "Hibiscus-Sense-Test-Device"
#define MQTT_CONTROL_RGB_TOPIC    "Hibiscus-Sense-Test-Device/RGB"
#define MQTT_CONTROL_LED_TOPIC    "Hibiscus-Sense-Test-Device/LED"
#define MQTT_TRIGGER_TOPIC        "Hibiscus-Sense-Test-Device/Trigger"

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

Adafruit_NeoPixel rgb(1, 16, NEO_GRB + NEO_KHZ800);

WiFiClient net;
MQTTClient mqtt;

unsigned long lastMillis, sendMillis = 0;

volatile bool buttonPressed = false;
int toggleValue = 0;

void IRAM_ATTR handleButtonPress() {
  buttonPressed = true;
}

void connectToWiFi() {
  Serial.print("\nConnecting to Wi-Fi '" + String(WIFI_SSID) + "' ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" connected!");

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.print("Local IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Network Signal Strength (RSSI): ");
  Serial.println(WiFi.RSSI());
}

void messageReceived(String &topic, String &payload) {
  Serial.println("MQTT SUBSCRIPTION ...");
  Serial.println("Subscribe Message Received: " + payload);

  if(topic == String(MQTT_CONTROL_RGB_TOPIC)){

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

  if(topic == String(MQTT_CONTROL_LED_TOPIC)){
    // Adjust the LED brightness based on the payload
    Serial.print("CONTROL LED ... ");
    digitalWrite(2, payload.toInt());
    Serial.println("OK");
  }

  Serial.println();
}

void connectToMqttBroker(){
  Serial.print("\nConnecting to '" + String(MQTT_HOST) + "' ...");
  
  mqtt.begin(MQTT_HOST, net);
  mqtt.onMessage(messageReceived);

  String uniqueString = String(WIFI_SSID) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];
  
  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);
  
  while (!mqtt.connect(uniqueClientID)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  Serial.println("Subscribe to: " + String(MQTT_CONTROL_RGB_TOPIC));
  mqtt.subscribe(String(MQTT_CONTROL_RGB_TOPIC));
  Serial.println("Subscribe to: " + String(MQTT_CONTROL_LED_TOPIC));
  mqtt.subscribe(String(MQTT_CONTROL_LED_TOPIC));

}

void setup() {
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable   detector

  rgb.begin();
  rgb.show();

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), handleButtonPress, FALLING);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  pinMode(13, OUTPUT);

  Serial.begin(115200);
  Serial.print("Hit Enter on the Serial Monitor input to continue ... ");
  while(!Serial.available());
  Serial.println("OK");
  
  Serial.print("Press the IO0 pushbutton to continue ... ");
  while(digitalRead(0) != LOW);
  Serial.println("OK");

  delay(1000);
  
  Serial.println("\nHIBISCUS SENSE");
  Serial.println();

  Serial.println("Initializing Sensors:");
  
  Serial.print("1. APDS9960 ... ");
  if (!apds.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");
  }

  Serial.print("2. BME280 ... ");
  if (!bme.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");
  }
  
  Serial.print("3. MPU6050 ... ");
  if (!mpu.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");    
  }
  Serial.println();

  apds.enableProximity(true);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.print("Initializing Wi-Fi ... ");

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No Wi-Fi!");
  }
  else {
    Serial.print(n);
    Serial.println(" Wi-Fi available:");
    for (int i = 0; i < n; ++i) {
      Serial.print("> ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(", RSSI: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBM, Channel: ");
      Serial.print(WiFi.channel(i));
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }

  connectToWiFi();
  connectToMqttBroker();
  
  Serial.println();

  Serial.println("-------------------------------------------------");

  Serial.println("ACTUATORS ...");
  Serial.println("1. Buzzer Buzz");
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 10){
    analogWrite(13, dutyCycle);
    delay(10);
  }
  analogWrite(13, 0);
  
  Serial.println("2. RGB LED Red Colour");
  rgb.setPixelColor(0, rgb.Color(255, 0, 0)); rgb.show();
  delay(300);

  Serial.println("   RGB LED Green Colour");
  rgb.setPixelColor(0, rgb.Color(0, 255, 0)); rgb.show();
  delay(300);

  Serial.println("   RGB LED Green Colour");
  rgb.setPixelColor(0, rgb.Color(0, 0, 255)); rgb.show();
  delay(300);

  Serial.println("   RGB LED OFF");
  rgb.setPixelColor(0, rgb.Color(0, 0, 0)); rgb.show();
  delay(300);

  Serial.println("3. Blue LED Blinking");
  digitalWrite(2, LOW); delay(100);
  digitalWrite(2, HIGH); delay(100);
  digitalWrite(2, LOW); delay(100);
  digitalWrite(2, HIGH); delay(300);

}

void loop() {

  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (!mqtt.connected()) {
    connectToMqttBroker();
  }

  if (buttonPressed) {
    toggleValue = !toggleValue;

    Serial.println("MQTT PUBLISHER ...");
    Serial.println("Publish Trigger: " + String(toggleValue));
    Serial.println();
    mqtt.publish(String(MQTT_TRIGGER_TOPIC), String(toggleValue));
    
    buttonPressed = false;
  }

  // Read sensor data and print periodically
  uint8_t proximity = apds.readProximity();

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float altitude = bme.readAltitude(1008);
  float barometer = bme.readPressure() / 100.0F;

  mpu.getEvent(&a, &g, &temp);

  float x_axis = a.acceleration.x;
  float y_axis = a.acceleration.y;
  float z_axis = a.acceleration.z;

  float x_gyro = g.gyro.x;
  float y_gyro = g.gyro.y;
  float z_gyro = g.gyro.z;

  if(millis() - lastMillis > 1000){
    Serial.println("-------------------------------------------------");

    lastMillis = millis();

    // Print sensor data
    Serial.println("SENSORS READING ...");
    
    Serial.println("1. Proximity: " + String(proximity));
    Serial.println("2. Temperature: " + String(temperature) + " °C");
    Serial.println("3. Humidity: " + String(humidity) + " %RH");
    Serial.println("4. Approx. Altitude: " + String(altitude) + " m");
    Serial.println("5. Barometer: " + String(barometer) + " hPa");
    Serial.println("6. Accelerometer X: " + String(x_axis) + ", Y: " + String(y_axis) + ", Z: " + String(z_axis) + " m/s^2");
    Serial.println("7. Gyrometer X: " + String(x_gyro) + ", Y: " + String(y_gyro) + ", Z: " + String(z_gyro) + " rad/s");

    Serial.println();
  }
  
  // publish a message roughly every second.
  if (millis() - sendMillis > 1000) {
    sendMillis = millis();

    Serial.println("PUBLISH DATA ...");

    String data = "{\"temperature\":" + String(temperature) + ",";
    data += "\"barometer\":" + String(barometer) + ",";
    data += "\"altitude\":" + String(altitude) + ",";
    data += "\"humidity\":" + String(humidity) + "}";

    Serial.println("Data to Publish: " + data);
    Serial.println("Length of Data: " + String(data.length()));
    Serial.println("Publish to: " + String(MQTT_PUBLISH_TOPIC));
  
    mqtt.publish(String(MQTT_PUBLISH_TOPIC), data);
  }
}