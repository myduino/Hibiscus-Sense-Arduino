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

const char ssid[] = "";
const char pass[] = "";
const char device_developer_id[] = "";
const char device_access_token[] = "";

long previousMillis = 0;

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);

// UDP and CoAP class
// other initialize is "Coap coap(Udp, 512);"
// 2nd default parameter is COAP_BUF_MAX_SIZE(defaulit:128)
// For UDP fragmentation, it is good to set the maximum under
// 1280byte when using the internet connection.
WiFiUDP udp;
Coap coap(udp, 1024);

char url[] = "coap.favoriot.com";
String method = "POST";
IPAddress host(159,65,134,213); //DNS lookup coap.favoriot.com
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

  WiFi.begin(ssid, pass);

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
  if(millis() - previousMillis > 10000){
    previousMillis = millis();
    
    String parameters = "{\"device_developer_id\":\"" + String(device_developer_id) + "\",\"data\":{";
    
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
    payloadJSON += "\"apikey\":\"" + String(device_access_token) + "\",";
    payloadJSON += "\"parameters\":" + parameters;
    payloadJSON += "}";

    char payload[1024];
    payloadJSON.toCharArray(payload, 1024);
    Serial.println("Send Request");
    int msgid = coap.send(host, port, url, COAP_CON, COAP_POST, NULL, 0, (uint8_t *)payload, strlen(payload));
  }

  coap.loop();
}
