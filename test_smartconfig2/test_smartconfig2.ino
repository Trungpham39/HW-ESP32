
#include "WiFi.h"
void setup() {

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
