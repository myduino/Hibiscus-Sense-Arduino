// global variable, named counter.
int counter = 0;

void setup() {
  // initialized ESP32 UART0 with speed 9600bps
  Serial.begin(9600);
}

void loop() {
  // increment counter variable by 1 on every loop.
  counter++;
  // transmit the variable counter value to computer
  Serial.println(counter);
  // wait for 1 second before next action.
  delay(1000);
}
