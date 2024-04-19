# Exercise 05 Serial Communication

The aim of this exercise is to demonstrate serial communication between the ESP32 microcontroller on the Hibiscus Sense board and your PC using the USB-to-Serial converter (CP2104) on the Hibiscus Sense board.

Serial Communication is a communication process, receiving and transmitting data between two devices, such as **_computer to computer_** or **_microcontroller to computer_** or **_microcontroller to microcontroller_**, by implementing hardware protocol known as `UART (Universal Asynchronous Receiver/Transmitter)`. The data were sent/receive bit by bit sequentially by UART over two or one transmission line (wires), with configurables speed known as `baud-rate` or `bits-per-second` (bps): _9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600_.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five.gif" width="200"></a></p>

The two transmission lines of UART, known as `RX (receive)` and `TX (transmit)`. The transmission begin by transmitting the data from TX port of one UART controller to RX port of the other UART controller.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five-a.png" width="400"></a></p>

There are 3x UART controllers available in ESP32:
UART | RX  | RX  |
---- | --- | --- |
UART0 | GPIO3 | GPIO1
UART1 | GPIO9 | GPIO10
UART2 | GPIO16 | GPIO17

On Hibiscus Sense, UART0 has been interfaced to Silicon Labs CP2104, which enable us to make serial communication between computer and ESP32. The UART0 also used for uploading the program into the ESP32. _While, UART1 has been used for SPI flash for the ESP32 module and UART1 RX has been used for WS2812 RGB LED._

Although, the hardware serial is ready, it woudld not initialized, unless we program the ESP32 to initialized its serial hardware. In Arduino programming, the default library for serial communication, known as `Serial`. We can use **Serial** library to program the ESP32 for serial communication. There are 5 main functions in `Serial` library for serial communication, they are:
1. `Serial.begin(_baud-rate_)` function, with 1 argument:
  - _baud-rate_ the speed of serial communication.
2. `Serial.print()` function transmit the data and print the data on the Serial Monitor, with 1 / 2 arguments:
  - 1 arguments:
    - `Serial.print(88)` transmit and print "88"
    - `Serial.print(1.23456)` transmit and print "1.23" (default 2 decimal places)
    - `Serial.print('H')` transmit and print "H"
    - `Serial.print("Hello, hibiscus!")` transmit and print "Hello, hibiscus!"
  - 2 arguments (optional) `base number or decimal points`:
    - `Serial.print(88, BIN)` transmit and print "1011000"
    - `Serial.print(88, OCT)` transmit and print "130"
    - `Serial.print(88, DEC)` transmit and print "88"
    - `Serial.print(88, HEX)` transmit and print "58"
    - `Serial.print(1.23456, 0)` transmit and print "1"
    - `Serial.print(1.23456, 2)` transmit and print "1.23"
    - `Serial.print(1.23456, 4)` transmit and print "1.2345"
3. `Serial.println()` function same as `Serial.print()`, with additional character of newline.
4. `Serial.available()` function use to check if the data is available in the buffer (holds 64 bytes).
5. `Serial.read()`function use to read the data inside the serial receive buffer.

We have understand main `Serial` library functions, now let's write a program ESP32 can transmit incremental value to Arduino IDE's Serial Monitor. The program as below:

## Complete Sketch
```cpp
// global variable named as counter with value 0
int counter = 0;

void setup() {
  // initialized ESP32 UART0 with speed 9600bps
  Serial.begin(9600);
}

void loop() {
  // increment variable counter's value by +1 on every loop.
  counter++;
  // transmit the variable counter's value to computer
  Serial.println(counter);
  // wait for 1 second before next action.
  delay(1000);
}
```
You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. Once done uploading, open the Serial Monitor. By observation, we can see an incremental value with newline is printed on the Arduino IDE Serial Monitor.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-five-b.gif" width="600"></a></p>

## Detail Sketch Explanations

To create incremental value, we can use (+) plus operator as it is an _addition_ arithmetic operations. We can create a global variable with `initial value of 0` and `int` integer data type.
```cpp
int counter = 0;
```

In the `void setup()` function, firstly we need to initialize the hardware serial communication by calling `begin()` function of `Serial` object, with suitable baud-rate, most commonly used is `9600`.
```cpp
Serial.begin(9600);
```

In logical thinking, before we can submit any value we need to have the value first, before we can submit it, right? Therefore, in the `void loop()` function, the first thing to do, is to generate _incremental value_ of variable `counter`, applying (++) arithmetic operations, representing +1 to the previous value of variable counter. Example of previous value of `counter` is `0` then add it by +1, the latest value of variable counter is 1, as thing process is inside the `void loop()` function, the variable counter's value incrementally by 1 each loop.
```cpp
counter++;
```

To transmit the value of variable counter with newline, we use `println()` function of `Serial` object, to do the task by refering the variable counter on the argument of `println()` function.
```cpp
Serial.println(counter);
```

Pause the task for a second before continue to the next action.
```cpp
delay(1000);
```

## Further Experiment
You can modify the data being sent/received and explore different baud rates and communication protocols.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>