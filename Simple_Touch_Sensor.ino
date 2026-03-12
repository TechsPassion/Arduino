#include <CapacitiveSensor.h>

/* * SETUP:
 * 1. Place the 10M resistor between Pin 4 and Pin 2.
 * 2. Attach your wire (with foil) to Pin 2.
 */

// Define the sensor: Pin 4 sends the pulse, Pin 2 receives it.
CapacitiveSensor mySensor = CapacitiveSensor(4, 2);

void setup() {
  // Pin 13 is the built-in LED on the Nano
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Start the serial monitor so we can see the numbers
  Serial.begin(9600);
}

void loop() {
  // 1. Read the sensor (30 samples for a steady reading)
  long value = mySensor.capacitiveSensor(30);

  // 2. Send the value to your computer screen
  Serial.println(value);

  // 3. Logic: If the value is high enough, someone is touching it!
  // '500' is a good starting point. If the LED stays on, try '1000'.
  if (value > 500) {
    digitalWrite(LED_BUILTIN, HIGH); // Light ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // Light OFF
  }

  // 4. A tiny pause to keep the Nano from working too hard
  delay(10);
}
