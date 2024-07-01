# Exercise 06: Monitor Pushbutton Status on GPIP0 (LED ON/OFF)

The aim of this exercise is to learn how to use a pushbutton (momentary switch) by reading the state of the pushbutton (pressed or released) and responding to button presses to turn ON the blue LED on the Hibiscus Sense board.

Pushbutton is a momentary switch that closed the circuit during press of the button, while the button is released, the circuit disconnected, such as shown in the animation below. It is not a toggle switch, where it has ON and OFF position. Pushbutton usually used to act as an input to trigger the system.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-six.gif" width="300"></a></p>

On Hibiscus Sense, there are two pushbutton:
1. **`RST`** push the button to reset the ESP32 program.
2. **`IO0`** connected to GPIO0.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-six-a.png" width="400"></a></p>

Both pushbutton in Hibiscus Sense applying [pull-up resistor](https://learn.sparkfun.com/tutorials/pull-up-resistors/all), to prevent floating voltage with capacitor to fix [debouncing effect](https://www.analog.com/en/technical-articles/better-way-to-push-your-buttons.html) of pushbutton. The circuit is complete when we push the **`IO0`** pushbutton, then ESP32 saw `LOW` state at `GPIO0`, because `GND` is connected to the junction of `GPIO0` in the circuit, as shown in the schematic below.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/schematic-exercise-six.png" width="300"></a></p>

Somehow, if a pushbutton circuit is applying pull-down resistor, as shown in the schematic below. ESP32 saw `HIGH` state at `GPIO0` when the IO0 pushbutton is pressed, because `3.3V` is connected to the junction of `GPIO0`. _This is **NOT** the circuit on Hibiscus Sense._

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/schematic-exercise-six-a.png" width="300"></a></p>

Since we know that ESP32 will sense `LOW` state at `GPIO0` during pushbutton pressed, so the program as follows:

## Complete Sketch
```cpp
void setup() {
  pinMode(0, INPUT);  // declaring GPIO0 as an INPUT pin.
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.

}

void loop() {
  // we use if() function to compare the GPIO0 reading state with the LOW state.
  // if the GPIO0 reading is LOW, light ON the LED on GPIO2 with LOW state.
  // else means, the GPIO0 reading is HIGH, light OFF the LED on GPIO2 with HIGH state.
  int pbstatus = digitalRead(0);
  if(pbstatus == LOW){
    digitalWrite(2, LOW);
  } 
  else {
    digitalWrite(2, HIGH);
  }
  
}
```

You can copy the sketch above, paste it into the Arduino IDE and upload the complete sketch to ESP32, then observe the output. Now we'll see the blue is turn OFF, as it will only turn ON once we pressed the IO0 pushbutton.

<p align="center"><a href="https://myduino.com/product/myd-036/"><img src="https://github.com/myduino/Hibiscus-Sense-Arduino/raw/main/references/image-exercise-six-b.gif" width="600"></a></p>

## Detail Sketch Explanations

In the `void setup()` function we declare two `pinMode()` function:
1. To declare GPIO0 as an INPUT pin, connected to the Pushbutton.
2. To declare GPIO2 as an OUTPUT pin, connected to the blue LED.
```cpp
pinMode(0, INPUT);  // declaring GPIO0 as an INPUT pin.
pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.
```

In the `void loop()` function we want to repeatedly monitor the state of GPIO0, either `LOW` or `HIGH` depending the action happen on the pushbutton, either `pressed` or `release`.
1. Create local variable named as `pbstatus` to store the current state of GPIO.
```cpp
 int pbstatus = digitalRead(0);
```
2. Applying `if()` function to **compare**, either the value of `pbstatus` variable _equal to_ `LOW` or else (`HIGH`). If the `pbstatus == LOW` turn ON the LED and if `pbstatus` equal to other than `LOW` turn OFF the LED.
```cpp
if(pbstatus == LOW){
  digitalWrite(2, LOW);
} 
else {
  digitalWrite(2, HIGH);
}
```

## Further Experiment

You can modify the code to perform different actions based on button presses or combine the pushbutton with other sensors or actuators for more complex interactions.

<p align="right"><a href="https://forms.gle/UgpDSFc46K4MkvTM8">&#128640; Tutorial Improvement & Suggestions</a></p>