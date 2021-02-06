/*
 * Hibiscus Sense - Exercise 05 Serial Communication
 * 
 * In Arduino ESP32 programming Serial library is used to program the UART controller
 * Main functions of Serial library are:
 * begin() function to initiate serial communication
 * print() function to transmit data
 * available() function to check if data is available in the receiving buffer
 * read() function to read data in receving buffer
 */

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
