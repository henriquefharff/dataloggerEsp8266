void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming string:
    String incomingString = Serial.readString();
    Serial.println(incomingString);
  }
}
