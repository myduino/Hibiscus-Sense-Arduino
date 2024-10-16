/*
 * Hibiscus Sense - Exercise 15 IoT using Favoriot CoAP Protocol
 * 
 * Author: Mohamad Ariffin Zulkifli
 * Organization: Myinvent Technologies Sdn Bhd
 *
 * This sketch has 3 summary execution steps:
 * 1. Initialized Wi-Fi conectivity
 * 2. Data Acquisition - Read data from the sensors
 * 3. Data Ingestion - Send data to Favoriot's data stream using CoAP protocol
 *
 * Install coap-simple library before using the sketch.
 * 
 * Select the board as ESP32 Dev Module before compiling the sketch
 * (example) Go to menu, Tools > Board > esp32 > ESP32 Dev Module
 * 
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include <coap-simple.h>

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

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);

WiFiUDP udp;
Coap coap(udp, 1024);

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Coap Response got]");

  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  //response from coap server
  if(packet.type==3 && packet.code==0){
    Serial.println("ping ok");
  }

  Serial.println("Stream Created");
}

void connect_to_wifi(){
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
}

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

  connect_to_wifi();

  // client response callback.
  // this endpoint is single callback.
  Serial.println("Setup Response Callback");
  coap.response(callback_response);

  // start coap server/client
  coap.start();

}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    connect_to_wifi();
  }
  
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
    
    String parameters = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    
    parameters += "\"proximity\":\"" + String(apds.readProximity()) + "\",";
    parameters += "\"altitude\":\"" + String(bme.readAltitude(1013.25)) + "\",";
    parameters += "\"barometer\":\"" + String(bme.readPressure()/100.00) + "\",";
    parameters += "\"humidity\":\"" + String(bme.readHumidity()) + "\",";
    parameters += "\"temperature\":\"" + String(bme.readTemperature()) + "\",";
    
    mpu.getEvent(&a,&g,&temp);
    
    parameters += "\"accx\":\"" + String(a.acceleration.x) + "\",";
    parameters += "\"accy\":\"" + String(a.acceleration.y) + "\",";
    parameters += "\"accz\":\"" + String(a.acceleration.z) + "\",";
    parameters += "\"gyrox\":\"" + String(g.gyro.x) + "\",";
    parameters += "\"gyroy\":\"" + String(g.gyro.y) + "\",";
    parameters += "\"gyroz\":\"" + String(g.gyro.z) + "\"";
    
    parameters += "}}";

    String payloadJSON = "{\"method\":\"POST\",";
    payloadJSON += "\"apikey\":\"" + String(deviceAccessToken) + "\",";
    payloadJSON += "\"parameters\":" + parameters;
    payloadJSON += "}";

    char payload[1024];
    payloadJSON.toCharArray(payload, 1024);
    
    Serial.println("\nSending data to Favoriot's Data Stream ...");
    Serial.println("Data to Send: " + payloadJSON);

    coap.send(
      IPAddress(159, 65, 134, 213), 
      5683, 
      "coap.favoriot.com", 
      COAP_CON, 
      COAP_POST, 
      NULL, 
      0, 
      (uint8_t *)payload, 
      strlen(payload)
    );
  }

  coap.loop();

  Serial.println("=============================================");
  delay(3000);
}