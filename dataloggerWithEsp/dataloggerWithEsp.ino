#include "FS.h"

int openFS()
{
  //Abre sistemas de arquivo
  if(!SPIFFS.begin())
  {
    return 1;
  }
  
  return 0;
}

String readSerialData()
{
  String data;
  if(Serial.available()>0)
  {
    data = Serial.readString();
    return data;
  }

  return "error";
}

void writeSerialData(String data)
{
  Serial.println(data);
}

void setup() 
{
  //iniciando serial
  Serial.begin(115200);
  //inicializa arquivos na serial
  if(openFS() != 0) 
  {
    while(openFS() != 0){};
  }
 
}

void loop() {
   String serialData;
     
   serialData = readSerialData();
   
   if(serialData != "error")
   {
     writeSerialData(serialData);
   }
}
