#include <WiFi.h> 
void setup() {
  pinMode(18, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
}

void loop() {
  int buttonStatus = digitalRead(18);    //Đọc trạng thái button
  if (buttonStatus == HIGH) { // Nếu mà button bị nhấn
    Serial.print("DEN ON");
  } else { // ngược lại
    Serial.print("DEN OFF");
  }
}
