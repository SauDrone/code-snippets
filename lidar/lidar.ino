#include <SoftwareSerial.h>
#include "TFMini.h"

SoftwareSerial mySerial(10, 11);      // Uno RX (TFMINI TX), Uno TX (TFMINI RX)
TFMini tfmini;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println ("Initializing...");
  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial);    
}


void loop() {
  // Take one TF Mini distance measurement
  uint16_t dist = tfmini.getDistance();
  uint16_t strength = tfmini.getRecentSignalStrength();

  // Display the measurement
  Serial.print(dist);
  Serial.print(" cm      sigstr: ");
  Serial.println(strength);

  // Wait some short time before taking the next measurement
  delay(25);  
}
