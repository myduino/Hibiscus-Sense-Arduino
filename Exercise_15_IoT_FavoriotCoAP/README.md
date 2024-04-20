# Exercise 15: IoT Application using Favoriot (CoAP Protocol)

The aim of this exercise is to learn how to send data to the Favoriot IoT platform using CoAP protocol.

This exercise is continuation from Exercise 13, therefore device, dashboard and rule on Favoriot remain same, only protocol being used by ESP32 to connect to Favoriot platform is change to CoAP.

## Sending Data to Favoriot using CoAP protocol

Let's sending the Hibiscus Sense sensor's data to Favoriot platform.

1. Open the sketch on Arduino IDE.

### Arduino Sketch

```cpp
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

char url[] = "coap.favoriot.com";
String method = "POST";
IPAddress host(159, 65, 134, 213); //DNS coap.favoriot.com
int port = 5683;

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

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

  // client response callback.
  // this endpoint is single callback.
  Serial.println("Setup Response Callback");
  coap.response(callback_response);

  // start coap server/client
  coap.start();
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

    String payloadJSON = "{\"method\":\"" + method + "\",";
    payloadJSON += "\"apikey\":\"" + String(deviceAccessToken) + "\",";
    payloadJSON += "\"parameters\":" + parameters;
    payloadJSON += "}";

    char payload[1024];
    payloadJSON.toCharArray(payload, 1024);
    
    Serial.println("\nSending data to Favoriot's Data Stream ...");
    Serial.println("Data to Send: " + payloadJSON);

    int msgid = coap.send(host, port, url, COAP_CON, COAP_POST, NULL, 0, (uint8_t *)payload, strlen(payload));
  }

  coap.loop();

  Serial.println("=============================================");
  delay(3000);
}

```

2. Replace these lines variable into your own details.

```cpp
const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";
```

3. Upload the sketch into the ESP32. Once done uploading open the Serial Monitor and observe the process and output on the Serial Monitor.

The program control the ESP32 to read and print the sensor's data with interval 3 seconds and interval 15 seconds send the data to Favoriot platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-coap-serial-monitor.png" width="800"></a></p>

Now, you can monitor the data on Favoriot's Data Stream.

On the Favoriot platform, go to menu and click **Data Stream** to show the list of data streaming from the Hibiscus Sense.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-data-stream.gif" width="800"></a></p>

Congratulations, you have completed this exercise and gain hands-on experience on how send data to the Favoriot IoT platform using secure MQTT connection.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>