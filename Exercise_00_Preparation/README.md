## Development Platform Preparation
Prior to start learning and hands-on, you have to make sure required tools below are ready:
1. **Hibiscus Sense**. If you don't own it yet, you can get it from :shopping_cart: [Myduino](https://myduino.com/product/myd-036/)
2. **USB Cable Type-A to Type-C**, because Hibiscus Sense's USB port is Type-C.
2. **Arduino IDE**. Download it from it's official website [Arduino Software](https://www.arduino.cc/en/software) page and install it on your PC.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-download.png" width="600"></a></p>

3. [**ESP32**](https://github.com/espressif/arduino-esp32) **Arduino Core**. If you don't have it yet on your Arduino IDE, follow this [instructions](https://github.com/myinvent/Hibiscus-Sense-Arduino/tree/main/Exercise_00_Preparation#install-esp32-arduino-core-using-arduino-ide-boards-manager).

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32.png" width="600"></a></p>

## Connect Hibiscus Sense to Computer's USB Port
Connect the USB cable Type-C to Hibiscus Sense and Type-A to our computer. Hibiscus Sense comes with preset program to test on-board actuators and sensors. Should be by now we'll see the buzzer is buzzing, the RGB LED changing colors, the blue LED blinking and the reading of sensors at Serial Monitor (we have to open the Arduino IDE Serial Monitor to see the data). Suppose, you didn't see any reaction on the board you can contact Mr. Ariffin via [WhatsApp](https://api.whatsapp.com/send?phone=60177875232&text=Hi%20Mr.%20Ariffin,%20please%20help.%20My%20Hibiscus%20Sense,%20seems%20not%20working%20for%20the%20first%20time.) for help.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time.gif" width="600"></a></p>

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-first-time-monitor.gif" width="600"></a></p>

### Install ESP32 Arduino Core using Arduino IDE Boards Manager.

1. On the Arduino IDE, go to menu: *File > Preferences*.
2. Click on *Window icon* beside the Additional board manager URLs field.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-menu-preferences-boards.png" width="600"></a></p>

3. Copy the URLs below and paste it into the Additional Boards Manager URLs field and click the *OK* button.
`https://espressif.github.io/arduino-esp32/package_esp32_index.json`

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-menu-preferences-board-url.png" width="600"></a></p>

4. Click the *OK* button to exit the Preferences window.
5. Open the *Boards Manager* on the left panel and search keyword: *esp32*
6. Look for *esp32* by Espressif and click the *INSTALL* button.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32-install.png" width="600"></a></p>

7. Wait until the installation process is done, which would take several minutes, until the status on the boards is *INSTALLED*.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32-installed.png" width="600"></a></p>

<p align="right"><a href="https://github.com/myinvent/hibiscus-sense-arduino#hibiscus-sense-esp32-arduino-tutorial">&#128285; Back to Top</a> | <a href="https://github.com/myinvent/hibiscus-sense-arduino#table-of-content">&#128203; Table of Content</a><br><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>