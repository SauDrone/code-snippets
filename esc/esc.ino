unsigned int  period = 4000; // Sampling period
unsigned long loop_timer;
unsigned long now, difference;

unsigned long pulse_length_esc1 = 1200;
void setup() {
  pinMode(8, OUTPUT);
}
void loop() {
  pulse_length_esc1 = pulse_length_esc1 + 10;
  if (pulse_length_esc1 >= 2000) {
    pulse_length_esc1 = 1200;
  }
  for (int i = 0; i < 100; i++) {
    applyMotorSpeed();
  }

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
