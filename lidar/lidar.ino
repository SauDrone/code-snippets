#include "TFMini.h"

//Arduino 19 -> Tfmini Green [TX]
//Arduino 20 -> Tfmini Blue [RX]
TFMini tfmini;

void setup() {
  Serial.begin(115200);
  Serial1.begin(TFMINI_BAUDRATE);
  Serial1.setTimeout(5);
  while (!Serial);
  Serial.println ("Initializing...");
  tfmini.begin(&Serial1);
}


void loop() {
  //-------------------
  long a = micros();
  uint16_t dist = tfmini.getDistance();
  String strDist=convertDistance(dist);
  long b = micros() - a;
  //-------------- 230 - 350 microsecond
  Serial.print(strDist);
  Serial.print(" cm  time");
  Serial.println(b);

  delay(50);
}

String convertDistance(uint16_t dist) {
  if (dist > 9999)
    dist = 9999;
    
  String strValue = "";
  if (dist < 10) {
    strValue = "000" + String(dist);
  }else if (dist < 100) {
    strValue = "00" + String(dist);
  }else if (dist < 1000) {
    strValue = "0" + String(dist);
  }else if (dist < 10000) {
    strValue = String(dist);
  }
  return strValue;
}
