//#include <ESP8266WiFi.h> // Bỏ comment dòng này để sử dụng cho ESP8266. Comment dòng này nếu sử dụng cho ESP32
#include <WiFi.h> // Bỏ comment dòng này để sử dụng cho ESP32. Comment dòng này nếu sử dụng cho ESP8266

const char *ssid = "Trung Pham";
const char *pw = "0904137650bo";

void setup() {
  // Đăng ký kênh Serial tại Baudrate 115200
  Serial.begin(115200);

  // Xuất lời chào
  Serial.println("MECHASOLUTION.VN");
  Serial.println("IoT Example: ESP to WIFI");
  
  // Xuất thông báo đang kết nối tới WiFi
  Serial.print("Dang ket noi toi WiFi ");
  Serial.print(ssid);

  // Thực hiện lệnh kết nối
  WiFi.begin(ssid, pw);
  
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

void loop() {
  
}
