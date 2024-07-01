# Hands-On Learning Preparation
Before we begin the hands-on activities to learn how to **`control the actuators`** and **`acquire data from the sensors`** on Hibiscus Sense, please ensure that the following hardware and software components are readily accesible on your desk and on your PC:
1. **Hibiscus Sense** and a **USB cable Type-A to Type-C**. If you don't own it yet, you are welcome to purchase it from :shopping_cart: [Myduino Website](https://myduino.com/product/myd-036/)
2. **Arduino IDE**.
3. **Arduino core for the ESP32**.

Let's prepare the required software and tools on your PC.

## Download and Install CP210x USB Driver on Your PC (8 Steps)

1. Download it from it's official website [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) or you can directly download the .zip file from this link [CP210x Universal Windows Driver](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip).

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-download.png" width="800"></a></p>

2. Locate the compressed file in the Downloads folder.

3. Click the **Extract all** button.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-zip.png" width="800"></a></p>

4. Click the **Extract** button.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-extract.png" width="600"></a></p>

5. Locate the extracted folder, right click on the **`silabser`** file and click the **Install** option.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-install.png" width="800"></a></p>

6. On the Open File - Security Warning pop-up window, click the **Open** button.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-open.png" width="400"></a></p>

7. On the User Access Control window, click the **Yes** button.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-allow.png" width="400"></a></p>

8. Wait until the installation is successful and click the **OK** button.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/silabs-cp210-successful.png" width="400"></a></p>

## Download and Install Arduino IDE (4 Steps)

1. Download it from it's official website [Arduino Software](https://www.arduino.cc/en/software) page. The current version is 2.3.2.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-download.png" width="800"></a></p>

Or you can directly download from here:
* [Windows 10 and newers (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Windows_64bit.exe)
* [Linux AppImage (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Linux_64bit.AppImage)
* [Linux Zip File (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Linux_64bit.zip)
* [Mac OS Intel, 10.15: "Catalina" or newer (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_macOS_64bit.dmg)
* [Mac OS Apple Silicon, 11: "Big Sur" or newer (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_macOS_arm64.dmg)

2. Double click the Arduino IDE installer file, to install the Arduino IDE.

<p align="center"><img src="https://docs.arduino.cc/static/cfcd7a208ddfc85c43a96d94773d5c8b/4ef49/downloading-and-installing-img01.png" width="800"></a></p>

3. Follow the instructions in the installation wizard, until the process is succesfully completed.

<p align="center"><img src="https://docs.arduino.cc/static/4d81f22769b64631460ea1c583aa5156/4ef49/downloading-and-installing-img02.png" width="800"></a></p>

4. You can run Arduino IDE on your PC!

## Install ESP32 Arduino Core using Arduino IDE Boards Manager (7 Steps)

1. On the Arduino IDE, go to menu: ***File > Preferences***.
2. Click on ***Window icon*** beside the Additional board manager URLs field.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-menu-preferences-boards.png" width="800"></a></p>

3. Copy the URLs below and paste it into the ***Additional Boards Manager URLs*** field and click the ***OK*** button.
**`https://espressif.github.io/arduino-esp32/package_esp32_index.json`**

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-menu-preferences-board-url.png" width="800"></a></p>

4. Click the ***OK*** button to exit the Preferences window.
5. Open the ***Boards Manager*** on the left panel and search keyword: ***esp32***
6. Look for ***esp32** by Espressif Systems* and click the **INSTALL** button (Current version is 3.0.1).

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-hardware-library-esp32-install.png" width="800"></a></p>

7. Wait until the installation process is done, which would take several minutes, until the status on the board is *`3.0.x installed`*.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-hardware-library-esp32-installed.png" width="800"></a></p>

## Connect Hibiscus Sense to Your PC (6 Steps)
1. Connect the USB cable Type-C to Hibiscus Sense and Type-A to your PC.
2. On the Arduino IDE, choose the correct *COM port* interfaced to CP2104 USB driver on Hibiscus Sense.

`On Windows OS` Example: *COM5*
<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-com-port.png" width="800"></a></p>

`On Mac OS` Example: */dev/cu.usbserial-XXXXXXXXX*
<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-com-port-mac.png" width="800"></a></p>

3. On the board selection, choose *ESP32 Dev Module*.

`On Windows OS`
<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-com-board.png" width="800"></a></p>

`On Mac OS`
<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/arduino-ide-com-board-mac.png" width="800"></a></p>

Hibiscus Sense, shipped with default sketch to check the sensors and list available Wi-Fi networks at your place. Let's continue to test it!

4. Click the *magnifying glass* icon at the right side of the Arduino IDE to open the *Serial Monitor*.
5. Set the Baud Rate to `115200`.
6. Click the `IO0` button on Hibiscus Sense. You will see the result of the sensor and Wi-Fi checking on the Serial Monitor.

<p align="center"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/hibiscus-first-time-monitor.png" width="800"></a></p>

If you did not see any result on the Serial Monitor or having challenges to connect the board to your PC, please contact Mr. Ariffin via [WhatsApp](https://api.whatsapp.com/send?phone=60177875232&text=Hi%20Mr.%20Ariffin,%20please%20help.%20My%20Hibiscus%20Sense,%20seems%20not%20working%20for%20the%20first%20time.), he can assist you.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>