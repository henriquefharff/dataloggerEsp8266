#include <FS.h>
 
#define LED_PIN 2

 
/**
  * @desc escreve conteúdo em um arquivo
  * @param string state - conteúdo a se escrever no arquivo
  * @param string path - arquivo a ser escrito
*/
void writeFile(String state, String path) { 
  //Abre o arquivo para escrita ("w" write)
  //Sobreescreve o conteúdo do arquivo
  File rFile = SPIFFS.open(path,"w+"); 
  if(!rFile){
    Serial.println("Erro ao abrir arquivo!");
  } else {
    rFile.println(state);
    Serial.print("gravou estado: ");
    Serial.println(state);
  }
  rFile.close();
}
 
/**
  * @desc lê conteúdo de um arquivo
  * @param string path - arquivo a ser lido
  * @return string - conteúdo lido do arquivo
*/
String readFile(String path) {
  File rFile = SPIFFS.open(path,"r");
  if (!rFile) {
    Serial.println("Erro ao abrir arquivo!");
  }
  String content = rFile.readStringUntil('\r'); //desconsidera '\r\n'
  Serial.print("leitura de estado: ");
  Serial.println(content);
  rFile.close();
  return content;
}
 
/**
  * @desc inicializa o sistema de arquivos
*/
void openFS(void){
  //Abre o sistema de arquivos
  if(!SPIFFS.begin()){
    Serial.println("\nErro ao abrir o sistema de arquivos");
  } else {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);   
  openFS();
   
  // no primeiro upload de programa o arquivo state.txt deve ser criado com o conteúdo "off"
  // no segundo upload a linha deve ser comentada.
  //writeFile("off", "/state.txt");
 
  // verifica o último estado do LED e ativa de acordo
  String state = readFile("/state.txt");
  if(state == "on") 
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else if(state == "off") 
  {
    digitalWrite(LED_PIN, LOW);
  }    
}
 
void loop() {
  /*
   * verifica o estado anterior salvo no arquivo, 
   * ativa o LED de acordo 
   * e escreve novo estado no arquivo.
   */
  if(Serial.read() == '1')
  {
    String state = readFile("/state.txt");    
    if(state == "off") 
    {
      writeFile("on", "/state.txt");
      digitalWrite(LED_PIN, LOW);
    }
    else if(state == "on") 
    {
      writeFile("off", "/state.txt");
      digitalWrite(LED_PIN, HIGH);      
    } 
  }
}
