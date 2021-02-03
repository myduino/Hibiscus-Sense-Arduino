/*
 * Hibiscus Sense Example Sketch - Pushbutton
 * 
 * There are 2x Pushbutton on-board, 1x for RESET button and 1x for BOOT and general purpose.
 * The pushbutton labeled IO0 is connected to GPIO0.
 * 
 * The pushbutton is connected to GND, therefore whenever it is pushed,
 * the circuit is completed and the GND signal interfaced to IO0 and
 * IO0 will sense LOW state, otherwise it is HIGH state.
 * 
 */

void setup() {
  
  pinMode(0, INPUT);  // declaring GPIO0 as an OUTPUT pin.
  pinMode(2, OUTPUT); // declaring GPIO2 as an OUTPUT pin.

}

void loop() {

  // we use if() function to compare the GPIO0 reading state with the LOW state.
  // if the GPIO0 reading is LOW, light ON the LED on GPIO2 with LOW state.
  // else means, the GPIO0 reading is HIGH, light OFF the LED on GPIO2 with HIGH state.
  if(digitalRead(0) == LOW) digitalWrite(2, LOW);
  else digitalWrite(2, HIGH);
  
}
