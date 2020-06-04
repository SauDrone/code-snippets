unsigned int  period = 4000; // Sampling period
unsigned long loop_timer;
unsigned long now, difference;
#include <Servo.h>
unsigned long pulse_length_esc1 = 1000;
void setup() {
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  /*digitalWrite(8, HIGH);
  delayMicroseconds(1000);
  digitalWrite(8, LOW);*/
  delay(10000);
  digitalWrite(13,1);
}
void loop() {
  
  
  if (Serial.available()){
    int val = Serial.parseInt(); 
  
  if(val < 1000 || val > 1900)
  {
    Serial.println("not valid");
  }
  else
  {
    pulse_length_esc1=val; // Send signal to ESC.
  }
  }

  applyMotorSpeed();
  
  

}

void applyMotorSpeed() {
  while ((now = micros()) - loop_timer < period);
  loop_timer = now;

  digitalWrite(8, HIGH);
  while (true) {
    now        = micros();
    difference = now - loop_timer;
    if (difference >= pulse_length_esc1) {
      digitalWrite(8, LOW);
      break;
    }
  }
}
