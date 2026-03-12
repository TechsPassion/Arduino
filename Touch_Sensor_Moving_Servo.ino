#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CapacitiveSensor.h>

// 1. Setup PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// 2. Setup Touch Sensor (10M resistor between 4 and 2)
CapacitiveSensor mySensor = CapacitiveSensor(4, 2);

// Servo Pulse Constants (Common for most servos)
#define SERVOMIN  150 // Minimum pulse length count (0 degrees)
#define SERVOMAX  450 // Maximum pulse length count (90 degrees)

void setup() {
  Serial.begin(9600);
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60Hz
  
  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);
}

void loop() {
  // Read the touch sensor
  long value = mySensor.capacitiveSensor(30);
  
  Serial.println(value);

  if (value > 500) { 
    // TOUCHED: Move servo to 0 degrees
    pwm.setPWM(0, 0, SERVOMIN);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // NOT TOUCHED: Move servo to 90 degrees
    pwm.setPWM(0, 0, SERVOMAX);
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(10);
}
