#include <Servo.h> // Include the Servo library
Servo servo; // Create a servo object

void setup() {
  servo.attach(11); // Attach the servo to pin 11
  Serial.begin(9600);
}

void loop() {
  
  int pressure; // Store the force value from 0 to 1023
  pressure = analogRead(0);
  servo.write(pressure/5); // Set servo angle to pressure
  Serial.println("Pressure:");
  Serial.println(pressure);
  delay(10);
  
}
