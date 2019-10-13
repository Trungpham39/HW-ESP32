#include "WiFi.h"
#include <EEPROM.h>

String idWifi, pwdWifi;
int ssidLength, pwdLength;

bool getWifiData(){
  ssidLength = readEEPROM(10).toInt();
  pwdLength = readEEPROM(13).toInt();

  //Checking EEPROM data 
  if(ssidLength > 0){
    idWifi = readEEPROM(16);
    pwdWifi = readEEPROM(16+ssidLength+1);
    printWifiDetail();
    return true;
  }
  else {
    printWifiDetail();
    return false;
  }
}

void printWifiDetail(){
  Serial.print("SSID: ");
  Serial.print(idWifi);
  Serial.print(" Length: ");
  Serial.println(ssidLength);

  Serial.print("Pwd: ");
  Serial.print(pwdWifi);
  Serial.print(" Length: ");
  Serial.println(pwdLength); 
}

void printWifiDetail1(){
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  Serial.print("Pwd: ");
  Serial.println(WiFi.psk());
  
}

bool setupWifi(){
  EEPROM.begin(512);
  bool wifiStorage = getWifiData();
  if(wifiStorage){
    if(idWifi.length() > 1){
      //Connect wifi with wifi data from EEPROM
      int count = 0;
      WiFi.begin(idWifi.c_str(), pwdWifi.c_str());
      while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
        count++; 
        //Try to connect wifi in 15s
        if(count==15){
          Serial.println("\nTime out! Can't connect lastest Wifi");
          Serial.println("Begin SmartConfig!");
          return setupSmartConfig();
        }
      }
    }
  }
  else return setupSmartConfig();
}

bool setupSmartConfig(){
  //initial smartconfig if don't have wifi storage
    Serial.println("Initial SmartConfig !!!");
    WiFi.beginSmartConfig();
    int count = 0;
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print(".");
      count ++;
      //If over 60 seconds SmartConfig can't setup success. Cancel SmartConfig
      if(count == 120){
        Serial.println("\nTime out! Failed to connect Wifi with SmartConfig!");
        WiFi.stopSmartConfig();
        return WiFi.smartConfigDone();
      }
    }
    Serial.println("Smartconfig done!");
    //add SSID & Pwd to EEPROM-----SSID storage to address 1------PWD storage to address 2
    
    Serial.print("connecting to wifi...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      count++;
      if(count == 60)
      {
        Serial.println("Time out! Can't connect to wifi with SmartConfig");
        return false;
      }
    }
    Serial.println("\ndone!");
    printWifiDetail1();
    int ssidLength = WiFi.SSID().length();
    int pwdLength = WiFi.psk().length();
    
    String sizeSSID = fixValue(ssidLength);
    String sizePwd = fixValue(pwdLength);

    clearLastedEEPROM();

    writeEEPROM(10, sizeSSID);
    writeEEPROM(13, sizePwd);

    writeEEPROM(16, WiFi.SSID());
    writeEEPROM(16 + ssidLength + 1, WiFi.psk());
    
    return WiFi.smartConfigDone();
}

String fixValue(int input)
{
  String output; 
  if(input < 10){
    output.concat("0");
    output.concat(input); 
  }
  else output.concat(input);
  Serial.print("Output: ");
  Serial.println(output);
  return output;
}

void clearLastedEEPROM(){
  int lastestAdd = 16+ssidLength+pwdLength;
  Serial.print("Lastest address: ");
  Serial.println(lastestAdd);
  for(int i = 10; i <= lastestAdd; i++){
    EEPROM.write(i,'\0');
  }
  EEPROM.commit();
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  
  bool checkWifiState = setupWifi();
  while(!checkWifiState){
    checkWifiState = setupWifi();
  }
  if(checkWifiState) {
    delay(300);
    Serial.println("Success to connect!");
    // Xuất địa chỉ IP được cấp bởi thiết bị router
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
