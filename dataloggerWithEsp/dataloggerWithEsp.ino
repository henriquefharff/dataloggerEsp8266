#include "FS.h"

int writeArchive(String content, String path)
{
  //Abre arquivo no modo escrita e no modo append
  File rFile = SPIFFS.open(path, "a");
  
  if(!rFile)
  {
    return 1;
  }
  
  rFile.println(content);
  rFile.close();
  
  return 0;
}
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
  int attemp=0;
  //iniciando serial
  Serial.begin(115200);
  //inicializa arquivos na serial
  if(openFS() != 0) 
  {
    while((openFS() != 0) && (++attemp<2));
  }
 
}

void loop() {
   String serialData;
   int attemp=0;
   
   serialData = readSerialData();
   if(serialData != "error")
   {
     
     if(writeArchive(serialData,"/logger.txt") != 0)
     {
      while(writeArchive(serialData,"/logger.txt") != 0) && (++attemp<2));
     }
   }
}
