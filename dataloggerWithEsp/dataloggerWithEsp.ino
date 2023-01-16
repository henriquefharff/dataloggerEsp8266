#include "FS.h"

#define READ_BUTTON 4 //GPIO4 - D2

int stateOfButton()
{
  int buttonRead = digitalRead(READ_BUTTON);
  return buttonRead;
}

int checkSizeOfArchive(File archive)
{
  //The size of all flash is 4mb
  //But we can use just 3mb for file system because 1mb it is for OTA
  
  uint32_t archiveSize=0;
  archiveSize = archive.size();

  if(archiveSize > 3000000)
  {
    Serial.print("\nFlash is full");
    return 1;
  }

  return 0;
  
}


String readArchive(String path)
{
  String data;
  File rFile = SPIFFS.open(path, "r");
  
  if(!rFile) 
  {
    return "error";
  }

  //verifica se ainda há dados para leitura
  while(rFile.available())
  {
    delay(1);
    data = rFile.readStringUntil('\n');
    writeSerialData(data);
  }

  rFile.close();
  return "ok";
}


int writeArchive(String content, String path)
{
  //Abre arquivo no modo escrita append
  File rFile = SPIFFS.open(path, "a");
  
  if((!rFile) && (checkSizeOfArchive(rFile)))
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
  //Button for read the serial.
  pinMode(READ_BUTTON, INPUT);
  
  //iniciando serial
  Serial.begin(115200);
  //inicializa arquivos na serial
  if(openFS() != 0) 
  {
    while(openFS() != 0);
  }
 
}

uint32_t tick=0;
void loop() {
   String serialData;
   int attemp=0;
    
   if(stateOfButton())
   {
    readArchive("/logger.txt");
    delay(100);
    Serial.end();
   }
   serialData = readSerialData();
   if(serialData != "error")
   { 
  
    //write data into flash
     if(writeArchive(serialData,"/logger.txt") != 0)
     {
      while((writeArchive(serialData,"/logger.txt") != 0) && (++attemp<2));
     }
     //Armazena o tick da última escrita / recebimento de dados
     tick = millis(); 
   }else
   {
    //Verifica se já passou 5 minutos desde o último dado recebido
    //Se for true, significa que o rádio finalizou os envios dos dados
    if((millis() - tick) > 300000)
    {
      Serial.print("\nFinish of sent data\n");
      delay(50);
      //ESP.deepSleep(0);
    }
   }

   
}
