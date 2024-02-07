In this exercise, we will begin the journey of Practical Internet of Things (IoT) with Arduino.

You might have heard IoT somewhere ... in Seminar, Webinar, Podcast, YouTube or even from your closest family and friends. But what actually is IoT? In simple words, IoT is a network of connected devices over the Internet, thus you can either control or monitor the devices over the Internet. In much better definition, **IoT is a _system_**, consists of network of connected devices over the Internet via middleware enabling bidirectional communication between human-to-machine or machine-to-machine in exchanging on-demand information resulting in better decision making.

There are 4 key components in IoT:
1. **`Things`**: The connected devices, consists of microcontroller (such as ESP32), sensors, actuators with Internet connectivity. [Hibiscus Sense](https://myduino.com/product/myd-036/) is an example of prototype IoT devices. [DDS45-LB Distance Sensor](https://myduino.com/product/drg-039/) is an example of end-product IoT devices.
2. **`Middleware`**: The cloud/server, which handle the inbound/outbound of data transmission and communication over the Internet, including data ingestion, data storage, data management, data analytics, etc. These are available IoT platform such as [Favoriot](https://platform.favoriot.com/), [Blynk](https://blynk.io/), [Thingspeak](https://thingspeak.com/), [Ubidots](https://ubidots.com/), [Thingsboard](https://thingsboard.io/), [ParticleIO](https://www.particle.io/) and more.
3. **`App`**: The software interface, where human can interact with the data. Software, visualise the data from the IoT devices in form of human readable format such as alert, notification, dashboard, and analytics interfaces. We can find the app in from of mobile app, desktop app or web app.
4. **`Internet`**. The Internet technology, such as Wi-Fi, Ethernet, Cellular (GSM/GPRS, 3G, 4G, 5G) and Satellite, is required for Internet connectivity around the world.

Any project without one of the components, it is not an IoT project. Therefore, in any IoT project, first thing to do is to choose the right IoT platform for our IoT project.

In this exercise, we choose Blynk as our IoT platform.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://osoyoo.com/driver/blynk/blynk-iot.png" width="700"></a></p>

**`Blynk`** is one of the most easiest IoT platform ever exist on the planet. Their solution, has most complete IoT components, which are:
- Things: They provide Blynk Arduino libraries - to enable the communication between the cloud and devices.
- Middleware: They provide Blynk Server - responsible for all the communications between the smartphone and the things.
- App: They provide Blynk app - we can create stunning dashboard or interfaces, using its various widgets.
- Internet: Not provided by them, but we can choose which Internet technology we want to use, such as `WiFi (ESP32)`, `Cellular (SIM900 GSM)` or `Ethernet (ENC28J60)`, Blynk provide the library.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/blynkkk/blynkkk.github.io/raw/master/images/GithubBanner.jpg" width="700"></a></p>

Prior to start program the Hibiscus Sense. Let's setup Blynk platform.

## Setup Blynk Platform

1. Click this link [https://blynk.cloud/dashboard/register](https://blynk.cloud/dashboard/register) to create your Blynk account.
2. as

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-email.png" width="800"></a></p>

There are 2 steps we need to complete, follow the instructions below:
1. [Getting Started with the Blynk App](https://docs.blynk.cc/#getting-started-getting-started-with-the-blynk-app-1-create-a-blynk-account)
2. [Getting Started With Hardware](https://docs.blynk.cc/#getting-started-getting-started-with-hardware)

In this exercise, we want to monitor:
1. Proximity
2. Altitude
3. Barometric pressure
4. Humidity
5. Temperature
6. Accelerometer, x-axis
7. Accelerometer, y-axis
8. Accelerometer, z-axis
9. Gyrometer, x-axis
10. Gyrometer, y-axis
11. Gyrometer, z-axis

Therefore in the sketch below, we program the ESP32 to acquire all the from APDS9960, BME280 and MPU6050. Then update the data to the Blynk app using `Blynk.virtualWrite()` function.

```cpp
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
```
Now, we can upload the complete sketch to ESP32, once done uploading observe the output on the Blynk App, while we can control the RGB LED and LED.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-twelve.gif" width="300"></a></p>

If you want to monitor and control Hibiscus Sense Blynk demo app, you can download the Blynk App and scan the QR code below:

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-twelve.png" width="200"></a></p>

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>