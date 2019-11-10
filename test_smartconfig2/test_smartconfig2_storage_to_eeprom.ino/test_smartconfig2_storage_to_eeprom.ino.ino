#include <IOXhop_FirebaseESP32.h>
#include <EEPROM.h>
#include <SPI.h>
#include "WiFi.h"
#include "WebServerModule.h"
#include "SmartConfigModule.h"

#define FIREBASE_HOST "hubbie-viper.firebaseio.com"
#define FIREBASE_AUTH "

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

    IPAddress ip(WiFi.localIP());
    IPAddress gateway(192,168,1,1);
    IPAddress subnet(255,255,255,0);
    IPAddress ipServer(192,168,137,153);
    clientConnectToServer(80, ipServer);
//    Server setup
//    setStaticIP(ip, gateway, subnet);
//    initialServer(80);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server state: "); Serial.println(isServerOn());    
    //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Firebase.setInt("/int",random(0, 30));
  //messageHandle();

  //Test messageHandle function
  clientSetMessage("123456");
  delay(1000);
  clientSetMessage("1234567");
//  if(isServerOn()){
//    messageHandle();
//  }
  delay(500);
}
