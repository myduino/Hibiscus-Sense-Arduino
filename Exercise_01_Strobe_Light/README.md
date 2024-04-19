# Exercise 01: Control Blue LED on GPIO2 (Strobe Light Effect)

The aim of this exercise is to control the blue LED on GPIO2, alternating the LED state between ON and OFF with a specific delay to create a strobe light effect on the Hibiscus Sense board.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/hibiscus-sense-exercise-one.png" width="400"></a></p>

There is 1x blue LED labelled as `LED` on-board, as circled on the image above. The circuit of this LED is an **active-low circuit**, as shown in the schematic below, which the negative (-ve) terminal of this LED is connected to GPIO2, therefore we have to pull the GPIO2 to LOW state, in order to complete the circuit, then the light of the LED will turn ON. Otherwise, by pulling the GPIO2 to HIGH state, the light of the LED will turn OFF.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one.png" width="150"></a></p>
 
This is quite unusual behaviour, but it is good to learn how an electronic circuit could behave either way. Whereas, the usual circuit design is **active-high circuit**, where the positive (+ve) terminal of the LED connected to the GPIO2, as in the schematic below, instead of the negative (-ve) terminal of the LED connected to GPIO2, as in the schematic above. According to this type of circuit, we need to pull GPIO2 to HIGH state, to turn ON the LED, otherwise pull GPIO2 to LOW state, to turn OFF the LED.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/schematic-exercise-one-a.png" width="150"></a></p>

Since, the blue LED circuit on Hibiscus Sense is active-low, we will program it as below:

## Complete Sketch
```cpp
void setup() {
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.
}

void loop() {
  // strobe light effect, such on the aeroplane.
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);

  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(2000);
}
```

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. By observation, the output of the LED only have 2 states, which are ON and OFF. This output signal known as **`DIGITAL OUTPUT`**.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one-a.gif" width="600"></a></p>

## Detail Sketch Explanations

The LED is connected to `GPIO2`. We want to control the output voltage 0V or 3.3V from GPIO2 to the LED, therefore in the `void setup()` function, we configure GPIO2 as `OUTPUT`.
```cpp
pinMode(2, OUTPUT);
```

In the `void loop()` function, the program start controlling the GPIO2 signal to `LOW` state to complete the LED circuit, which the LED turn ON. Then `delay()` function to pause the program in `100` milliseconds. The, the signal state `HIGH` which disconnecting the circuit, makes the LED turn OFF. The process continued, and making alternate ON and OFF of the Blue LED.

```cpp
digitalWrite(2, LOW); // LED ON
delay(100);
digitalWrite(2, HIGH);  // LED OFF
delay(100);

digitalWrite(2, LOW);
delay(100);
digitalWrite(2, HIGH);
delay(2000);
```

**Interesting facts!** This exercise is mimicking the strobe light on an aeroplane during the night.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/image-exercise-one.gif" width="300"></a></p>

## Further Experiment
You can modify the delay time to change the strobe speed or experiment with different LED colors or patterns on different GPIO numbers.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>