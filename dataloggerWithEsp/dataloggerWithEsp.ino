#include <Arduino.h>

int data=0;
 
void setup() {
 Serial.begin(9600);
}
 
void loop() {
  data = Serial.read();
  if(data=='2')
  {
    Serial.print("Boa meu bruxo\n");
    data-=48;
    Serial.println(data, DEC);
  }
}
