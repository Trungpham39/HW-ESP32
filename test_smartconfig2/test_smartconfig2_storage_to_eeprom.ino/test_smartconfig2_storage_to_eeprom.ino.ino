#include <IOXhop_FirebaseESP32.h>
#include <EEPROM.h>
#include "WiFi.h"
#include "SmartConfigModule.h"

#define FIREBASE_HOST "hubbie-viper.firebaseio.com"
#define FIREBASE_AUTH ""

int byte1, byte2, byte3, byte4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);
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
    byte1 = WiFi.localIP()[0];
    byte2 = WiFi.localIP()[1];
    byte3 = WiFi.localIP()[2];
    byte4 = WiFi.localIP()[3];
    Serial.print("IP Address: ");
    Serial.print(byte1);
    Serial.print(".");
    Serial.print(byte2);
    Serial.print(".");
    Serial.print(byte3);
    Serial.print(".");
    Serial.println(byte4);            
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Firebase.setInt("/int",random(0, 30));
  //delay(1000);
}
