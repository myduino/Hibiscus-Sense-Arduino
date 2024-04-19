# Exercise 12: IoT Application using Blynk IoT Platform

The aim of this exercise is to create an Internet of Things (IoT) project by integrating the Hibiscus Sense board and the Blynk platform over the Internet. Sending sensor data (e.g., temperature, humidity) to the Blynk app and controlling actuators (e.g., LED, buzzer) from the Blynk app.

In this exercise, you will begin the journey of Practical Internet of Things (IoT) with Blynk IoT platform using Hibiscus Sense.

## What is IoT?

You might have heard IoT somewhere ... in Seminar, Webinar, Podcast, YouTube or even from your closest family and friends.

But what actually is IoT?

In simple words, IoT is a network of connected devices over the Internet, which you can remotely control or monitor the devices over the Internet.

For more technical definition, **IoT is a _system_**, consists of network of connected devices over the Internet via middleware (cloud computers) enabling bidirectional communication between human-to-machine or machine-to-machine in exchanging on-demand information resulting in better decision making.

There are 4 Key Components in IoT:
1. **`Smart Things`**: The connected devices, consists of microcontroller (such as ESP32), sensors, actuators with Internet connectivity. [Hibiscus Sense](https://myduino.com/product/myd-036/) is an example of prototype IoT devices. [DDS45-LB Distance Sensor](https://myduino.com/product/drg-039/) is an example of end-product IoT devices.
2. **`Network`**. The Internet technology, such as `Wi-Fi`, `Ethernet`, `Cellular` (2G, 3G, 4G, 5G) and `Satellite`, is required for Internet connectivity around the world. The gateways enabling low-power wireless devices to connect to the Internet.
3. **`Middleware`**: The cloud/server, which handle the inbound/outbound of data transmission and communication over the Internet, including data ingestion, data storage, data management, data analytics, etc. These are available IoT platform such as [Favoriot](https://platform.favoriot.com/), [Blynk](https://blynk.io/), [Thingspeak](https://thingspeak.com/), [Ubidots](https://ubidots.com/), [Thingsboard](https://thingsboard.io/), [ParticleIO](https://www.particle.io/) and more.
4. **`Applications`**: The software interface, where human can interact with the data. Software, visualise the data from the IoT devices in form of human readable format such as alert, notification, dashboard, and analytics interfaces. We can find the app in from of mobile app, desktop app or web app.

According to AltexSoft, in any IoT applications, it might uses number of layers, the key of IoT building blocks or its components remain the same:

<p align="center"><a href="https://www.altexsoft.com/blog/iot-architecture-layers-components/"><img src="https://www.altexsoft.com/static/blog-post/2023/11/e04ab4a6-f337-4af8-b276-3f93c019414f.webp" width="700"></a></p>

Any project without one of the components, is not considered as an IoT project. In IoT project, first thing to do is to choose the most suitable IoT platform for our IoT project.

In this exercise, we choose Blynk as our IoT platform.

## Introduction to Blynk IoT Platform

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://osoyoo.com/driver/blynk/blynk-iot.png" width="700"></a></p>

**`Blynk`** is one of the most easiest IoT platform ever exist on the planet. Their solution, has most complete IoT components, which are:
- `Things`: They provide Blynk Arduino libraries - to enable the communication between the cloud and devices.
- `Middleware`: They provide Blynk Server - responsible for all the communications between the smartphone and the things.
- `App`: They provide Blynk app - we can create stunning dashboard or interfaces, using its various widgets.
- `Internet`: Not provided by them, but we can choose which Internet technology we want to use, such as `WiFi (ESP32)`, `Cellular (SIM900 GSM)` or `Ethernet (ENC28J60)`, Blynk provide the library.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/blynkkk/blynkkk.github.io/raw/master/images/GithubBanner.jpg" width="700"></a></p>

Prior to start program the Hibiscus Sense. Let's setup Blynk platform.

## Setup Blynk Platform

1. Click this link [https://blynk.cloud/dashboard/register](https://blynk.cloud/dashboard/register) to create your Blynk account.
2. Fill in your email in the **EMAIL** field, **check** on *I agree to Terms and Conditions and accept Privacy Policy* and click the **Sign Up** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-email.png" width="800"></a></p>

3. Go to your email and look for the email from Blynk.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-confirm-email.png" width="800"></a></p>

4. Click the **Create Password** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-link-password.png" width="800"></a></p>

5. Fill in your password in the **PASSWORD** field, make sure to follow the password specifications and click the **Next** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-create-password.png" width="800"></a></p>

6. Fill in your name in the **FIRST NAME** field and click the **Done** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-profile.png" width="800"></a></p>

7. Click the **Skip** button, to skip the Blynk Tour.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-skip-tour.png" width="800"></a></p>

8. Click the **Cancel** button, to skip the Quickstart process.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-cancel-quickstart.png" width="800"></a></p>

Good, you have successfully setup account on the Blynk platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-register-welcome.png" width="800"></a></p>

## Install Blynk Library on Arduino IDE

Before you can program the Hibiscus Sense to connect to Blynk platform, install the Blynk library on the Arduino IDE.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-library-blynk.png" width="800"></a></p>

## Let's Get Started Exercise

In this exercise, we would like to learn how to:
1. Monitor on Blynk dashboard:
- Humidity
- Temperature

2. Control on Blynk dashboard:
- LED

In total, there are 3 data streaming over the Internet on the Blynk platform:
1. **Humidity**, with data type **Double**, minimum value **0** and maximum value **100**.
2. **Temperature**, with data type **Double**, minimum value **0** and maximum value **60**.
3. **LED**, with data type **Integer**, minimum value **0** and maximum value **1**.

### Create a **Blynk Template** with **3 Datastreams**

1. On the left panel, click the **Developer Zone**.
2. Click the **+ New Template** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-developer-zone.png" width="800"></a></p>

3. Fill in the template name **Hibiscus Sense** on the **NAME** field.
4. Choose **ESP32** as the **HARDWARE**.
5. Choose **WiFi** as the **CONNECTION TYPE**.
6. Click the **Done** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-create-template.png" width="800"></a></p>

7. Click the **Datastreams** tab.
8. Click the **+ New Datastream** dropdown button and choose **Virtual Pin**.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-create-datastream.png" width="800"></a></p>

9. Click the **icon** dropdown button and select **droplet** icon.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-icon.png" width="800"></a></p>

10. Change the **NAME** field to **Humidity**.
11. Choose the virtual **PIN** to begin with **V0**.
12. Choose **Double** as the DATA TYPE.
13. Choose **Percentage, %** as the UNIT.
14. Fill in **0** as the MIN value.
15. Fill in **100** as the MAX value.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-info.png" width="800"></a></p>

16. Click the **colour** dropdown button and select **blue** colour to represent humidity value.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-color.png" width="800"></a></p>

17. Click the **Create** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-create.png" width="800"></a></p>

Good, a datastreams has been created for humidity value. Let's continue next steps to complete other 2 datastreams.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-created.png" width="800"></a></p>

18. On the **Humidity** datastreams row, hover mouse to **Actions** column and click the **copy** icon.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-copy.png" width="800"></a></p>

19. Replace the icon with **temperature icon**, **NAME** field to ***Temperature***, colour to **red colour**, **UNIT** selection to ***Celsius, °C***, **MAX** to ***60*** and click the **Create** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-temperature.png" width="800"></a></p>

20. Repeat step 18 to copy the datastream configuration.
21. Replace the icon with **lamp icon**, **NAME** field to ***LED***, colour to **green colour**, **DATA TYPE** selection to ***Integer***, **UNIT** selection to ***None***, **MAX** to ***0*** and click the **Create** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pin-led.png" width="800"></a></p>

22. Click the **Save** button, to save the datastreams configuration.

Good, you have successfully create 3 datastreams with assigned Virtual Pin:
1. Humidity, V0
2. Temperature, V1
3. LED, V2

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-virtual-pins.png" width="800"></a></p>

### Configure the **Blynk Dashboard**

1. Click the **Web Dashboard** tab.
2. Click the **Edit** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-edit.png" width="800"></a></p>

3. On the **Widget Box**, scroll down and find **Gauge** widget.
4. Drag the **Gauge** widget into the **Dashboard**.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-humidity-add.png" width="800"></a></p>

5. Hover the mouse to the **Gauge** widget and click on the **Gear** icon to configure the widget.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-humidity-config.png" width="800"></a></p>

6. Fill in the **TITLE** to ***Humidity***, **Datastream** select to ***Humidity (V0)***, change the **color** and click the **Save** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-humidity-info.png" width="800"></a></p>

7. Copy the widget, by hovering your mouse to the **Humidity** widget and click the **copy** icon.
8. Replace the **TITLE** to ***Temperature***, **Datastream** select to ***Temperature (V1)***, change the **color** and click the **Save** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-temperature-info.png" width="800"></a></p>

9. On the **Widget Box**, scroll and find **Switch** widget and drag the **Gauge** widget into the **Dashboard**.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-led-add.png" width="800"></a></p>

10. Fill in the **TITLE** to ***LED***, **Datastream** select to ***LED (V2)***, change the **color** and click the **Save** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-led-info.png" width="800"></a></p>

11. Click the **Save** button, to save the dashboard.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard-save.png" width="800"></a></p>

### Create the **Device**

1. On the left panel, click the **Devices**.
2. Click the **+ New Device** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-device-create.png" width="800"></a></p>

3. Choose to create new device **From Template**.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-device-create-template.png" width="800"></a></p>

4. Choose **Hibiscus Sense** and give name ***Hibiscus Sense*** and click the **Create** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-device-create-new.png" width="800"></a></p>

Good, your device has successfully created.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-device-created.png" width="800"></a></p>

Let's program the device.

### Program the Device

To connect Hibiscus Sense to Blynk platform, you need to program the ESP32 including with Blynk Device Information, which can be accessed and copied from the Device Info.

1. On the Device page, click the **Device Info** tab.
2. Click the on the **FIRMWARE CONFIGURATION** field to **copy** the Blynk Device Information.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-device-created.png" width="800"></a></p>

3. Open the Arduino IDE with new sketch.
4. Copy the sketch below into the new sketch.

```cpp
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
//#define BLYNK_AUTH_TOKEN            "YourAuthToken"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_BME280.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

Adafruit_BME280 bme;

long previousMillis = 0;

BLYNK_WRITE(V2){
  int value = param.asInt();

  pinMode(2, OUTPUT);
  digitalWrite(2, value);
}

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!bme.begin()){
    Serial.println("Failed to find Hibiscus Sense BME280 chip");
  }
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass);

    while(WiFi.status() != WL_CONNECTED);
  }

  Blynk.run();

  if(millis() - previousMillis > 1000){

    previousMillis = millis();

    float humidity = bme.readHumidity();
    float temperature = bme.readTemperature();

    Serial.println("Humidity: " + String(humidity) + " %RH");
    Serial.println("Temperature: " + String(temperature) + " °C");

    Blynk.virtualWrite(V0, humidity);
    Blynk.virtualWrite(V1, temperature);

  }
}
```

5. Replace the copied Blynk Device Information in the sketch.
6. Replace the Wi-Fi **ssid** and Wi-Fi **password** information.
7. Upload the complete sketch to ESP32.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/blynk-dashboard.png" width="800"></a></p>

## Further Experiment
You can customize the Blynk app interface with additional widgets.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>