#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//Connect the PCA9685 To A4 and A5 pins are SDA/SCL. Also VCC, GND
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    pwm.setPWM(i, 0, SERVOMAX);
  }
  delay(1000);
  for (int i = 0; i < 4; i++) {
    pwm.setPWM(i, 0, SERVOMIN);
  }
  delay(1000);
}
