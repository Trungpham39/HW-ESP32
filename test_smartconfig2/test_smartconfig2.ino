
#include "WiFi.h"
#include <EEPROM.h>

String idWifi;
String pwdWifi;

void checkWifiStorge(){
  EEPROM.begin(512);
  //Read SSID from EEPROM
  idWifi = readEEPROM(1);
  pwdWifi = readEEPROM(20);
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

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println("");
  WiFi.mode(WIFI_STA);
  delay(500);


  Serial.print("smart config...");
  WiFi.beginSmartConfig();
  while (!WiFi.smartConfigDone()) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("done!");

  Serial.print("ssid:");
  Serial.println(WiFi.SSID());
  Serial.print("password:");
  Serial.println(WiFi.psk());

  Serial.print("connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("done!");
  
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
