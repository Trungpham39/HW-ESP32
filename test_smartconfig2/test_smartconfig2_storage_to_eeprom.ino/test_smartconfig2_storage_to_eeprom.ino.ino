#include "WiFi.h"
#include <EEPROM.h>

String idWifi;
String pwdWifi;

bool checkWifiStorage(){
  EEPROM.begin(512);
  //Read SSID from EEPROM
  idWifi = readEEPROM(10);
  pwdWifi = readEEPROM(11);

  if(idWifi.length() > 1 && pwdWifi.length() > 1){
    return true;
  }
  else return false;
}


String readEEPROM(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void writeEEPROM(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}

  char *stringToCharArray(String input){
  int stringLength = input.length();
  char output[stringLength+1];
  strcpy(output, input.c_str());
  return output;
}

void wifiSetup(bool checkData){
  Serial.println("");
  WiFi.mode(WIFI_STA);
  delay(200);
  if (!checkData){
    //initial smartconfig if don't have wifi storage
    WiFi.beginSmartConfig();
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Smartconfig done!");
    //add SSID & Pwd to EEPROM-----SSID storage to address 1------PWD storage to address 2
    writeEEPROM(10, WiFi.SSID());
    writeEEPROM(11, WiFi.psk());
  }

  else WiFi.begin(stringToCharArray(idWifi), stringToCharArray(pwdWifi));

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();

  // Xuất thông báo đã kết nối thành công
  Serial.println("Ket noi thanh cong!");
  // Xuất địa chỉ IP được cấp bởi thiết bị router
  Serial.print("Dia chi IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  
  bool checkData = checkWifiStorage();
  wifiSetup(checkData);
}

void loop() {
  // put your main code here, to run repeatedly:

}
