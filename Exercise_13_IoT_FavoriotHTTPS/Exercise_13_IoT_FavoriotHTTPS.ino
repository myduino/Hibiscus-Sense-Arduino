#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel rgb(1, 16);

Adafruit_APDS9960 apds;
Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";
char device_developer_id[] = "YourDeviceDeveloperId";

long previousMillis = 0;

void setup() {

  Serial.begin(9600);

  rgb.begin();
  rgb.show();

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

    HTTPClient http;

    http.begin("https://apiv2.favoriot.com/v2/streams", "25204d063c95695e2d257959e9217bb76a84f55c");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", "YourAPIKey");

    int httpCode = http.POST(json);

    if(httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.println("HTTP Error!");
    }

    http.end();
  }
}
