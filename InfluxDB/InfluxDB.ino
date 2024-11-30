#include <Adafruit_Sensor.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <WiFi.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define DEVICE "Hibiscus Sense"
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define INFLUXDB_URL "http://YOUR_IP_ADDRESS:8086"
#define INFLUXDB_TOKEN "YOUR_INFLUXDB_TOKEN"
#define INFLUXDB_ORG "OUR_INFLUXDB_ORG_ID"
#define INFLUXDB_BUCKET "hibiscus_sense"
#define TZ_INFO "UTC8"

// Initialize sensors and sensor event variables
Adafruit_BME280 bme;

// Initialize InfluxDB client
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point bme280_data("environment");

unsigned long sendMillis = 0;

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

void setup() {
  Serial.begin(115200);

  Serial.println("HIBISCUS SENSE");
  Serial.println();

  Serial.println("Initializing Sensors:");

  // Initialize and configure BME280 sensor
  Serial.print("BME280 ... ");
  if (!bme.begin()){
    Serial.println("ERROR!");
  }
  else{
    Serial.println("OK");
  }

  // Connect to Wi-Fi router
  connectToWiFi();

  // Syncing with NTP servers time
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.println();
}

void loop() {
  // Reconnect to Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  if (millis() - sendMillis > 10000) {
    sendMillis = millis();

    Serial.println("SENSORS MEASUREMENT ...");
    Serial.println("1. Temperature: " + String(temperature) + " °C");
    Serial.println("2. Humidity: " + String(humidity) + " %RH");
    Serial.println("3. Barometer: " + String(pressure) + " hPa");

    Serial.print("SEND DATA TO INFLUXDB ... ");

    // Clear fields from previous iteration
    bme280_data.clearFields();

    // Read BME280 environmental data
    bme280_data.addField("temperature", temperature);
    bme280_data.addField("humidity", humidity);
    bme280_data.addField("pressure", pressure);

    // Write point
    if (!client.writePoint(bme280_data)) {
      Serial.print("FAILED: ");
      Serial.println(client.getLastErrorMessage());
    }

    Serial.println("OK");
    Serial.println();
  }
}