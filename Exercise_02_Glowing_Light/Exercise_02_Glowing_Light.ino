void setup() {
  ledcSetup(0, 5000, 8);

}

void loop() {
  ledcAttachPin(2, 0);
  
  for(int brightness = 255; brightness >= 0; brightness--){   
    ledcWrite(0, brightness);
    delay(15);
  }

  delay(200);

}
