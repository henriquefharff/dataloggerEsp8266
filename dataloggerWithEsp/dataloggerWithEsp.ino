String readSerialData(){
  String data;
  if(Serial.available()>0)
  {
    data = Serial.readString();
    return data;
  }

  return "error";
}

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
}

void loop() {
   String serialData;
   
   serialData = readSerialData();
   
   if(serialData != "error")
   {
     Serial.println(serialData);
   }
}
