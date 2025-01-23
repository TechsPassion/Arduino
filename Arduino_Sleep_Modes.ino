#include <avr/sleep.h>

const int wakeUpPin = 2; // Pin used for external interrupt (for Power-down mode)
const int ledPin = 13;   // Onboard LED connected to pin 13

void setup() {
  pinMode(wakeUpPin, INPUT_PULLUP); // Use internal pull-up resistor for the interrupt pin
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Choose Arduino sleep mode:");
  Serial.println("1: Idle");
  Serial.println("2: ADC Noise Reduction");
  Serial.println("3: Power-save");
  Serial.println("4: Power-down");
  Serial.println("5: Standby");

  while (Serial.available() == 0) {} // Wait for user input

  int mode = Serial.parseInt();
  Serial.print("Entering mode: ");
  Serial.println(mode);

  switch (mode) {
    case 1: idleMode(); break;
    case 2: adcNoiseReductionMode(); break;
    case 3: powerSaveMode(); break;
    case 4: powerDownMode(); break;
    case 5: standbyMode(); break;
    default: Serial.println("Invalid mode");
  }
  delay(1000); // Small delay before re-entering loop
}

// Idle Mode:
// - CPU sleeps, peripherals and timers can still run.
// - Lowest power saving.
// - Wake up from any interrupt or activity (e.g., serial communication, pin change).
// - Use Case: Save power while keeping peripheral activities running, such as maintaining a real-time clock
void idleMode() {
  set_sleep_mode(SLEEP_MODE_IDLE); 
  sleep_enable();                  
  sleep_mode();                    
  sleep_disable();                 
  Serial.println("Woke up from Idle Mode");
  blinkLED();
}

// ADC(Analog-to-Digital Converter) Noise Reduction Mode:
// - Similar to Idle, but ADC is disabled for lower noise.
// - Useful for analog readings after wake-up.
// - Use Case: When you need high-accuracy ADC(Analog-to-Digital Converter). readings in low-noise conditions.
// - Wake up from ADC conversion complete interrupt or other enabled interrupts.
void adcNoiseReductionMode() {
  set_sleep_mode(SLEEP_MODE_ADC); 
  sleep_enable();
  sleep_mode();
  sleep_disable();
  Serial.println("Woke up from ADC Noise Reduction Mode");
  blinkLED();
}

// Power-save Mode:
// - Timer/Counter2 continues to run (can be used for timed wake-up).
// - Allows the asynchronous timer to run, which can maintain a timer-based wake-up system.
// - Most other peripherals are disabled.
// - Moderate power saving.
// - Use Case: Suitable for devices that require periodic wake-ups for short tasks.
// - Wake up from any interrupt or activity (External interrupt, asynchronous timer).
void powerSaveMode() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  Serial.println("Woke up from Power-save Mode");
  blinkLED();
}

// Power-down Mode:
// - Deepest sleep mode, consumes the least power.
// - Almost everything is shut down.
// - Use Case: Ideal for long periods of inactivity, such as battery-operated devices.
// - Wake up from external interrupts, watchdog timer, and asynchronous timer (Timer2).
void powerDownMode() {
  // Configure external interrupt on pin 2 (wakeUpPin) connect to GND to wake up
  attachInterrupt(digitalPinToInterrupt(wakeUpPin), wakeUp, LOW); 

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();

  detachInterrupt(digitalPinToInterrupt(wakeUpPin)); 
  Serial.println("Woke up from Power-down Mode");
  blinkLED();
}

// Standby Mode:
// - Similar to Power-down, but the external oscillator is kept running.
// - Faster wake-up times than Power-down.
// - Use Case: For systems that need minimal power with faster wake-up times.
// - Wake up from external interrupts, watchdog timer, and asynchronous timer (Timer2).
void standbyMode() {
  set_sleep_mode(SLEEP_MODE_STANDBY);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  Serial.println("Woke up from Standby Mode");
  blinkLED();
}

// ISR for Wake-up
void wakeUp() {
  // Interrupt Service Routine, does nothing here as wake-up is handled after interrupt
}

// Function to blink LED 3 times after wake-up
void blinkLED() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
