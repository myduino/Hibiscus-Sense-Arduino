# Exercise 13: IoT Application using Favoriot (HTTPS Protocol)

The aim of this exercise is to create an Internet of Things (IoT) project by integrating secure HTTP connection between the Hibiscus Sense board and the Favoriot IoT platform:
1. Setting Up a Favoriot Account.
2. Setting Up IoT Device.
3. Sending Data to Favoriot using secure HTTP connection.
4. Visualizing Data on Favoriot Dashboard.
5. Creating Rules for Data Alert & Notification.

## Introduction to Favoriot IoT Platform

[Favoriot Platform](https://www.favoriot.com/favoriotplatform) is an IoT platform developed by [Favoriot Sdn. Bhd.](https://www.favoriot.com/), to simplify IoT devices and it's data management, allowing you to easily perform IoT data pipeline, including data ingestion, data visualization, data analytics, data alert and notification from your IoT devices.

<p align="center"><img src="https://platform.favoriot.com/tutorial/v2/images/architecture%20v2.png" width="500"></a></p>

## Setting Up Favoriot Account

1. Click this link [https://platform.favoriot.com/registration](https://platform.favoriot.com/registration) to create your Favoriot account and click the **Continue with Email** button. You can also use your Gmail account to register.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-register.png" width="800"></a></p>

2. Fill in your information in the form including **First Name**, **Last Name**, **Purpose**, **Organisation**, **Country**, **User ID**, **Password** and **Email**.
3. Click the **Get Code** button to get the verification code.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-register-get-code.png" width="800"></a></p>

3. Go to your email and look for the email from Favoriot.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-register-code.png" width="600"></a></p>

4. Copy the verification code and paste it on the **Verification Code** field and click the **Register** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-register-insert-code.png" width="800"></a></p>

5. On the login page, fill in your **User ID** and **Password** and click the **Sign In** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-login.png" width="800"></a></p>

Good, you have successfully setup account on the Favoriot IoT platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-overview.png" width="800"></a></p>

## Setting Up IoT Device

Upon, succesful account registration, Favoriot automatically create the [platform hierarchy](https://platform.favoriot.com/tutorial/v2/#favoriot-platform-hierarchy), from the **`projectDefault`** > **`applicationDefault`** > **`groupDefault`** > **`deviceDefault`**.

Following the image below, go to menu and click **Hierarchy** > **Devices** to show the list IoT devices.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-default.png" width="800"></a></p>

### Delete deviceDefault

Only 1 device is allowed on FREE ACCOUNT plan, let's **delete** the deviceDefault and create new device instead.

1. Click the **`trash bin`** icon under the **`Action`** column.
2. Click the **`Delete`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-default-delete.png" width="800"></a></p>

3. Click the **`Understood`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-default-delete-confirm.png" width="800"></a></p>

4. Click the **`Delete`** button to confirm deletion of the deviceDefault from the device list.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-default-delete.png" width="800"></a></p>

### Create New Device

1. Save as the Hibiscus Sense below image into your PC.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-hibiscus-sense.jpg" width="300"></a></p>

2. Click the **`Create Device`** icon.
3. Choose group **Hierarchy**: **`groupDefault`**.
4. Key in **Device Name**: **`HibiscusSense`**
5. Key in **Description**: **`Hibiscus Sense`**
6. Choose **Device Type**: **`ESP32`** 

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-info-a.png" width="800"></a></p>

7. Key in **Latitude** and **Longitude**. *You can use Google to find your location latitude and longitude.*

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-latitude.png" width="800"></a></p>

8. Choose **Timezone**: **`Asia/Kuala_Lumpur`**
9. Click **`Select Photo`** to add device image.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-info-b.png" width="800"></a></p>

10. Click the **`Upload Image`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-info-upload.png" width="800"></a></p>

11. Choose the downloaded Hibiscus Sense image from **Step 1**.
12. Click the **`Done`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-info-image.png" width="800"></a></p>

13. Click the **`Confirm`** button to create the new device.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-info-confirm.png" width="800"></a></p>

Good, you have successfully create new device on the Favoriot platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-success.png" width="800"></a></p>

### Device Developer ID and Access Token

Click the **`eye`** icon under the **`Action`** column, to view the device information.

**Note**: **`Device Developer ID`** and **`Device Access Token`**, will be used in the Arduino sketch for ESP32 to create successful HTTP connection to Favoriot platform. *There is **copy** icon beside the field, for you to easily copy the details and paste into the Arduino sketch.*

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-success-info-a.png" width="800"></a></p>

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-device-success-info-b.png" width="800"></a></p>

## Sending Data to Favoriot using secure HTTP connection

Let's sending the Hibiscus Sense sensor's data to Favoriot platform.

1. Open the sketch on Arduino IDE.

### Arduino Sketch

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_NeoPixel.h>
#include "FavoriotCA.h"

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

  // STEP 1: Initialized Wi-Fi conectivity
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

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
    
    String json = "{\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",\"data\":{";
    
    json += "\"proximity\":\"" + String(apds.readProximity()) + "\",";
    json += "\"humidity\":\"" + String(bme.readHumidity()) + "\",";
    json += "\"altitude\":\"" + String(bme.readAltitude(1013.25)) + "\",";
    json += "\"barometer\":\"" + String(bme.readPressure()/100.00) + "\",";
    json += "\"temperature\":\"" + String(bme.readTemperature()) + "\",";
    
    mpu.getEvent(&a,&g,&temp);
    
    json += "\"accx\":\"" + String(a.acceleration.x) + "\",";
    json += "\"accy\":\"" + String(a.acceleration.y) + "\",";
    json += "\"accz\":\"" + String(a.acceleration.z) + "\",";
    json += "\"gyrox\":\"" + String(g.gyro.x) + "\",";
    json += "\"gyroy\":\"" + String(g.gyro.y) + "\",";
    json += "\"gyroz\":\"" + String(g.gyro.z) + "\"";
    
    json += "}}";

    Serial.println("\nSending data to Favoriot's Data Stream ...");

    WiFiClientSecure *client = new WiFiClientSecure;

    if(client) {
      client -> setCACert(FavoriotCA);
      {
        HTTPClient https;
      
        https.begin(*client, "https://apiv2.favoriot.com/v2/streams");
      
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Apikey", deviceAccessToken);
        
        int httpCode = https.POST(json);
      
        if(httpCode > 0){
          Serial.print("HTTPS Request: ");
          
          httpCode == 201 ? Serial.print("Success, ") : Serial.print("Error, ");
          Serial.println(https.getString());
        }
        else{
          Serial.println("> HTTPS Request Connection Error!");
        }
      
        https.end();
        Serial.println();
      }

      delete client;
    }
    else{
      Serial.println("Unable to create secure client connection!");
      Serial.println();
    }
  }

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

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-https-serial-monitor.gif" width="800"></a></p>

Let's monitor the data on Favoriot's Data Stream.

### Favoriot Data Stream

On the Favoriot platform, go to menu and click **Data Stream** to show the list of data streaming from the Hibiscus Sense.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-data-stream.gif" width="800"></a></p>

Good, now you have successfully send the sensor's data to the Favoriot platform.

Once, the data is available on Favoriot platform, let's create the dashboard to visualize the data streaming.

## Visualizing Data on Favoriot Dashboard

On the Favoriot platform, go to menu and click **Dashboards** to show the list of dashboards. Currently, we don't have any dashboard, let's create the dashboard!

### Create Dashboard
1. Click on the **`Create Dashboard`** icon.
2. Key in **Dashboard Name**: **`Hibiscus Sense`**
3. Key in **Tags**: **`proximity, humidity, altitude, barometer, temperature, accx, accy, accz, gyrox, gyroy, gyroz`**
4. Upload the image of Hibiscus Sense.
5. Click the **`Confirm`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-create-new.png" width="800"></a></p>

Good, you have successfully create new dashboard on the Favoriot platform.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-list.png" width="800"></a></p>

Click on the **Hibiscus Sense** dashboard and configure the dashboard.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new.png" width="800"></a></p>

### Configure Dashboard

#### Add Gauge Widget
1. Click the **`+`** icon at the right bottom of the page.
2. Key in **Title**: **`Humidity`**
3. Choose **Type**: **`Gauge`**
4. Choose **Gauge Type**: **`Basic`**
5. Choose **Device**: **`HibiscusSense`**
6. Choose **Parameter**: **`humidity`**
7. Key in **Parameter Unit**: **`%RH`**
8. Click the **`Confirm`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new-widget-gauge.png" width="800"></a></p>

Gauge widget is now shown on the dashboard.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new-gauge.png" width="800"></a></p>

### Add Line Widget

1. Click the **`+`** Add Widget icon at the right bottom of the page.
2. Key in **Title**: **`Humidity`**
3. Choose **Type**: **`Line`**
4. Choose **Line Curve**: **`Straight`**
5. Choose **Device**: **`HibiscusSense`**
6. Choose **Parameter**: **`humidity`**

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new-widget-line-a.png" width="800"></a></p>

7. Key in **X-Axis Label**: **`Time`**
8. Key in **Y-Axis Label**: **`humidity`**
9. Key in **Prefill Data Count**: **`30`**
10. Click the **`Confirm`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new-widget-line-b.png" width="800"></a></p>

Line widget is now shown on the dashboard.

Good, you have successfully configure the dashboard for data streaming visualization.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-device-new-line.png" width="800"></a></p>

If you want to edit the widget, you can click the **Edit Widget** icon.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-dashboard-live.png" width="800"></a></p>

You can click the **`X`** Exit Edit Mode icon at the right bottom of the page, to go to live mode.

**Note**: You might want to add other widget, but on FREE ACCOUNT plan, only 2 widget are allowed.

You can subscribe to BEGINNER PLAN plan, then you can add extra widget to visualize other data parameter.

## Creating Rules for Data Alert & Notification

Go to menu and click **Rules** to show the list of rules. Currently, we don't have any rule, let's create the rule!

1. Click on the **`Create Rule`** icon.
2. Click the **`Notifications`** icon.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-rule-new-notification.png" width="800"></a></p>

3. Choose the **Method**: **`Email`**
4. Key in the **Rule Name**: **`highHumidity`**
5. Key in the **`Description`**: **`High Humidity > 80`**
6. Choose the **Device**: **`HibiscusSense`**

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-rule-new-notification-a.png" width="800"></a></p>

7. Key in the **Rule**: **`stream.humidity > 80`**
8. Key in the  **To**: **`YOUR_EMAIL_ADDRESS`**
9. Key in the  **Notification Message**: **`[Hibiscus Sense]: The humidity value detected higher than 80 %RH`**
10. Choose the **Status**: **`Activate`**
11. Choose the **Threshold**: **`5`**
12. Click the **`Confirm`** button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-rule-new-notification-b.png" width="800"></a></p>

Good, you have successfully create the rule that will trigger an email if the humidity value is detected more than 80 %RH.

Simulate the humidity data to be above 80 %RH. Go to your Hibiscus Sense dashboard, monitor the humidity value to be more than 80 %RH.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-rule-humidity-detected.png" width="800"></a></p>

Once the Favoriot rule is detected, it will send an email notification.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-rule-humidity-email.png" width="800"></a></p>

Congratulations, you have completed this exercise and gain hands-on experience on how to create IoT applications using Favoriot platform.

## Further Experiment
You can upgrade your Favoriot account to BEGINNER PLAN and you can have the privileges to add new devices and explore more features on Favoriot platform.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>