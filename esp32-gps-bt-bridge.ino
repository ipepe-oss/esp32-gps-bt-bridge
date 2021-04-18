#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int GPS_MODULE_ENABLE = 4;
int baudRateMessage[] = {181, 98, 6, 0, 20, 0, 1, 0, 0, 0, 208, 8, 0, 0, 0, 194, 1, 0, 7, 0, 7, 0, 0, 0, 0, 0, 196, 150, 181, 98, 6, 0, 1, 0, 1, 8, 34};

void setGPSBaudRateToHigher(){
  while(!Serial2.available()){
    delay(50);
  }
  for(int i=0; i<37; i++){
    Serial2.write(baudRateMessage[i]);
  }
}

void setGPSRefreshRateTo10Hz(){
  Serial.println("Not setGPSRefreshRateTo10Hz");
  //Serial2.print("B5 62 06 08 06 00 64 00 01 00 01 00 7A 12 B5 62 06 08 00 00 0E 30");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  SerialBT.begin("ESP32-GPS"); //Bluetooth device name
  pinMode(GPS_MODULE_ENABLE, OUTPUT);
  digitalWrite(GPS_MODULE_ENABLE, HIGH);
  setGPSBaudRateToHigher();
//  Serial2.begin(115200);
  setGPSRefreshRateTo10Hz();
}

void loop() {
  if (Serial.available()) {
    Serial2.write(Serial.read());
//    SerialBT.write(Serial.read());
  }
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
//  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }
  delay(20);
}
