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
