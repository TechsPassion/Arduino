#include <CapacitiveSensor.h>

// Create a CapacitiveSensor object (using pins 2 and 4)
CapacitiveSensor capSensor = CapacitiveSensor(2, 4);

int threshold = 1000;    // Sensitivity threshold value
int ledPin = 13;         // LED pin
bool ledState = false;   // Variable to store the current state of the LED (ON/OFF)
bool lastTouch = false;  // Store the previous touch state
unsigned long debounceTime = 10; // Debounce time in milliseconds
unsigned long lastTouchTime = 0; // Store the last time a touch was detected

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  digitalWrite(ledPin, LOW); // Start with LED OFF
}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(30); // Read sensor value
  
  Serial.println(sensorValue); // Print the value for debugging
  
  bool isTouched = sensorValue > threshold; // Check if sensor is touched

  // Debouncing: Make sure the touch event is stable
  if (isTouched && !lastTouch && (millis() - lastTouchTime > debounceTime)) {
    ledState = !ledState;          // Toggle the LED state
    digitalWrite(ledPin, ledState); // Update the LED based on the new state
    lastTouchTime = millis();      // Update the time of the last touch
  }

  // Update the lastTouch state for the next loop iteration
  lastTouch = isTouched;
  
  delay(10); // Small delay for stability
}
