# Exercise 13: IoT Application using Favoriot (HTTPS Protocol)

The aim of this exercise is to create an Internet of Things (IoT) project by integrating the Hibiscus Sense board and the Favoriot IoT platform:
1. Setting Up a Favoriot Account
2. Sending Data to Favoriot
3. Visualizing Data on Favoriot Dashboard
4. Creating Rules

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

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/favoriot-hibiscus-sense.jpg" width="500"></a></p>

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