#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2
#define CHANNEL4 3

#define YAW      0
#define PITCH    1
#define ROLL     2
#define THROTTLE 3


// aileron  ->10
// elevator ->11
// throttle ->12
// rudder   ->13


// ---------------- Receiver variables ---------------------------------------
// Previous state of each channel (HIGH or LOW)
volatile byte previous_state[4];

// Duration of the pulse on each channel of the receiver in µs (must be within 1000µs & 2000µs)
volatile unsigned int pulse_length[4] = {1500, 1500, 1500, 1500};

// Used to calculate pulse duration on each channel
volatile unsigned long current_time;
volatile unsigned long timer[4]; // Timer of each channel

// Used to configure which control (yaw, pitch, roll, throttle) is on which channel
int mode_mapping[4];
 
 void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
configureChannelMapping();

    // Configure interrupts for receiver
    PCICR  |= (1 << PCIE0);  // Set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT4); // Set PCINT0 (digital input 8) to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT5); // Set PCINT1 (digital input 9) to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT6); // Set PCINT2 (digital input 10)to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT7); // Set PCINT3 (digital input 11)to trigger an interrupt on state change

  
  

}

void loop() {
  Serial.print("yaw:");
  Serial.print( pulse_length[mode_mapping[YAW]]);
  Serial.print(" pitch:");
  Serial.print( pulse_length[mode_mapping[PITCH]]);
  Serial.print(" roll:");
  Serial.print( pulse_length[mode_mapping[ROLL]]);
  Serial.print(" throttle:");
  Serial.println( pulse_length[mode_mapping[THROTTLE]]);

}

void configureChannelMapping() {
    mode_mapping[YAW]      = CHANNEL4;
    mode_mapping[PITCH]    = CHANNEL2;
    mode_mapping[ROLL]     = CHANNEL1;
    mode_mapping[THROTTLE] = CHANNEL3;
}

/**
 * This Interrupt Sub Routine is called each time input 8, 9, 10 or 11 changed state.
 * Read the receiver signals in order to get flight instructions.
 *
 * This routine must be as fast as possible to prevent main program to be messed up.
 * The trick here is to use port registers to read pin state.
 * Doing (PINB & B00000001) is the same as digitalRead(8) with the advantage of using less CPU loops.
 * It is less convenient but more efficient, which is the most important here.
 *
 * @see https://www.arduino.cc/en/Reference/PortManipulation
 * @see https://www.firediy.fr/article/utiliser-sa-radiocommande-avec-un-arduino-drone-ch-6
 */
ISR(PCINT0_vect) {
        current_time = micros();

        // Channel 1 -------------------------------------------------
        //PB4= pin 10
        if (PINB & B00010000) {                                        // Is input 10 high ?
            if (previous_state[mode_mapping[ROLL]] == LOW) {                     // Input 10 changed from 0 to 1 (rising edge)
                previous_state[mode_mapping[ROLL]] = HIGH;                       // Save current state
                timer[mode_mapping[ROLL]] = current_time;                        // Save current time
            }
        } else if (previous_state[mode_mapping[ROLL]] == HIGH) {                 // Input 10 changed from 1 to 0 (falling edge)
            previous_state[mode_mapping[ROLL]] = LOW;                            // Save current state
            pulse_length[mode_mapping[ROLL]] = current_time - timer[mode_mapping[ROLL]];   // Calculate pulse duration & save it
        }

        // Channel 2 -------------------------------------------------
        //PB5= pin 11
        if (PINB & B00100000) {                                        // Is input 11 high ?
            if (previous_state[mode_mapping[PITCH]] == LOW) {                     // Input 11 changed from 0 to 1 (rising edge)
                previous_state[mode_mapping[PITCH]] = HIGH;                       // Save current state
                timer[mode_mapping[PITCH]] = current_time;                        // Save current time
            }
        } else if (previous_state[mode_mapping[PITCH]] == HIGH) {                 // Input 11 changed from 1 to 0 (falling edge)
            previous_state[mode_mapping[PITCH]] = LOW;                            // Save current state
            pulse_length[mode_mapping[PITCH]] = current_time - timer[mode_mapping[PITCH]];   // Calculate pulse duration & save it
        }

        // Channel 3 -------------------------------------------------
        //PB6= pin 12
        if (PINB & B01000000) {                                        // Is input 12 high ?
            if (previous_state[mode_mapping[THROTTLE]] == LOW) {                     // Input 12 changed from 0 to 1 (rising edge)
                previous_state[mode_mapping[THROTTLE]] = HIGH;                       // Save current state
                timer[mode_mapping[THROTTLE]] = current_time;                        // Save current time
            }
        } else if (previous_state[mode_mapping[THROTTLE]] == HIGH) {                 // Input 12 changed from 1 to 0 (falling edge)
            previous_state[mode_mapping[THROTTLE]] = LOW;                            // Save current state
            pulse_length[mode_mapping[THROTTLE]] = current_time - timer[mode_mapping[THROTTLE]];   // Calculate pulse duration & save it
        }

        // Channel 4 -------------------------------------------------
        //PB7= pin 13
        if (PINB & B10000000) {                                        // Is input 13 high ?
            if (previous_state[mode_mapping[YAW]] == LOW) {                     // Input 13 changed from 0 to 1 (rising edge)
                previous_state[mode_mapping[YAW]] = HIGH;                       // Save current state
                timer[mode_mapping[YAW]] = current_time;                        // Save current time
            }
        } else if (previous_state[mode_mapping[YAW]] == HIGH) {                 // Input 13 changed from 1 to 0 (falling edge)
            previous_state[mode_mapping[YAW]] = LOW;                            // Save current state
            pulse_length[mode_mapping[YAW]] = current_time - timer[mode_mapping[YAW]];   // Calculate pulse duration & save it
        }
}
