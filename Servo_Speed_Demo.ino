/*
 * 3-in-1 Servo Speed Demo
 * Runs each method for 10 seconds.
 * * WIRING:
 * Servo Signal -> Pin 9
 * Servo Power  -> 5V
 * Servo Ground -> GND
 */

#include <Arduino.h>
#include <ServoEasing.hpp> // Install "ServoEasing" from Library Manager

ServoEasing myServo; 

const int SERVO_PIN = 9;

void setup() {
  Serial.begin(9600);
  
  // Attach the servo
  if (myServo.attach(SERVO_PIN) == INVALID_SERVO) {
    while(true); // Stop if error
  }
  
  // Settings for the Easing part
  myServo.setSpeed(50); // Medium speed
  myServo.setEasingType(EASE_CUBIC_IN_OUT); 
}

void loop() {
  // --- MODE 1: THE JUMP (Normal) ---
  runJumpMode(); 

  // --- MODE 2: THE LOOP (Linear Slow) ---
  runLoopMode();

  // --- MODE 3: THE EASING (Smooth) ---
  runEasingMode();
}

// ==================================================
// MODE 1: Normal "Jump" (10 Seconds)
// ==================================================
void runJumpMode() {
  unsigned long startTime = millis();
  Serial.println("Mode 1: Jump");

  // Run for 10 seconds (10000 milliseconds)
  while (millis() - startTime < 10000) {
    myServo.write(180);  // Snap to 180
    delay(1000);
    
    myServo.write(0);    // Snap to 0
    delay(1000);
  }
}

// ==================================================
// MODE 2: For Loop "Linear" (10 Seconds)
// ==================================================
void runLoopMode() {
  unsigned long startTime = millis();
  int pos = 0;
  Serial.println("Mode 2: Linear Loop");

  while (millis() - startTime < 10000) {
    // Slow move UP
    for (pos = 0; pos <= 180; pos += 1) { 
      myServo.write(pos);              
      delay(5); // Speed adjustment
    }
    
    // Slow move DOWN
    for (pos = 180; pos >= 0; pos -= 1) { 
      myServo.write(pos);              
      delay(5); 
    }
  }
}

// ==================================================
// MODE 3: Servo Easing "Smooth" (10 Seconds)
// ==================================================
void runEasingMode() {
  unsigned long startTime = millis();
  Serial.println("Mode 3: Smooth Easing");

  while (millis() - startTime < 10000) {
    myServo.easeTo(180); // Moves smoothly and waits until done
    delay(500);
    
    myServo.easeTo(0);   // Moves smoothly and waits until done
    delay(500);
  }
}
