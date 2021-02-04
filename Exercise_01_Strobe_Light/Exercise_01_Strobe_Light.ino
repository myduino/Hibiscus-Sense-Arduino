/*
 * Hibiscus Sense - Exercise 01 Strobe Light
 * 
 * There is 1x blue LED.
 * This LED is connected to GPIO2 of ESP32 microcontroller.
 * The circuit is an active-low circuit, therefore we need to pull the pins LOW,
 * in order to complete the circuit to the GND.
 * 
 * Therefore in the sketch,
 * we need to call LOW state in the digitalWrite function, to light ON the LED,
 * while call HIGH state, to light OFF the LED.
 * 
 */

void setup() {
  // declaring GPIO2 as an OUTPUT pin.
  pinMode(2, OUTPUT);

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
