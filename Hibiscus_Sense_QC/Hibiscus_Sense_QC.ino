#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <MQTT.h>
#include <Wire.h>

#define WIFI_SSID             "myinvententerprise"
#define WIFI_PASSWORD         "04222682"
#define MQTT_HOST             "broker.hivemq.com"
#define MQTT_PUBVLISH_TOPIC   "60177875232/Hibiscus-Sense"
#define MQTT_SUBSCRIBE_TOPIC  "60177875232/Hibiscus-Sense"

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

Adafruit_NeoPixel pixels(1, 16, NEO_GRB + NEO_KHZ800);

int freq = 2000;
int channel = 0;
int resolution = 8;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi '" + String(WIFI_SSID) + "' ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
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

void connectToMqttBroker(){
  Serial.print("Connecting to '" + String(WIFI_SSID) + "' ...");
  
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

  Serial.println("Subscribe to: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC));
  
  mqtt.subscribe(String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC));

}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); pixels.show();

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(13, channel);

  Serial.begin(115200);
  while(!Serial.available());

  delay(1000);

  Serial.println("HIBISCUS SENSE");
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

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No WiFi!");
  }
  else {
    Serial.print(n);
    Serial.println(" WiFi available:");
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

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.print("Network Signal Strength (RSSI): ");
  Serial.println(WiFi.RSSI());

  WiFi.begin(ssid, pass);
  
  client.begin("broker.hivemq.com", net);
  client.onMessage(messageReceived);

  connect();
  
  Serial.println();

}

void loop() {

  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  Serial.println("-------------------------------------------------");

  Serial.println("ACTUATORS ...");
  Serial.println("1. Buzzer Buzz");
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 10){
    ledcWrite(channel, dutyCycle);
    delay(10);
  }
  ledcWrite(channel, 0);
  
  Serial.println("2. RGB LED Red Colour");
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); pixels.show();
  delay(300);

  Serial.println("   RGB LED Green Colour");
  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); pixels.show();
  delay(300);

  Serial.println("   RGB LED Green Colour");
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); pixels.show();
  delay(300);

  Serial.println("   RGB LED OFF");
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); pixels.show();
  delay(300);

  Serial.println("3. Blue LED Blinking");
  digitalWrite(2, LOW); delay(100);
  digitalWrite(2, HIGH); delay(100);
  digitalWrite(2, LOW); delay(100);
  digitalWrite(2, HIGH); delay(300);

  Serial.println();

  Serial.println("SENSORS READING ...");
  Serial.print("1. Proximity: ");
  uint8_t proximity = apds.readProximity();
  Serial.println(proximity);
  delay(300);
  
  Serial.print("2. Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
  delay(300);

  Serial.print("3. Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  delay(300);

  Serial.print("4. Approx. Altitude: ");
  Serial.print(bme.readAltitude(1013.25));
  Serial.println(" m");
  delay(300);

  Serial.print("5. Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %RH");
  delay(300);

  mpu.getEvent(&a, &g, &temp);

  Serial.print("6. Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  delay(300);

  Serial.print("7. Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  delay(300);

  Serial.println();
  
  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    String data = "{\"temperature\":" + String(bme.readTemperature()) + ",";
    data += "\"humidity\":" + String(bme.readHumidity()) + "}";
  
    client.publish("60177875232/Monash-Malaysia", data);
  }
}