
#include <Servo.h> // Include the Servo library
Servo servo; // Create a servo object
// Define the connections for pins X, Y, and SW
const int X = A0, Y = A1, SW = 2;

void setup() {
  servo.attach(11); // Attach the servo to pin 11
  // Set pins X, Y, and SW to input mode
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(SW, INPUT_PULLUP);  // Use internal pull-up resistor
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Output analog readings of pin X
  Serial.print("X: ");
  servo.write(analogRead(X)/6); // Set servo angle to X degrees
  Serial.print(analogRead(X)/6); // Print the value being sent to the servo
  // Output analog readings of pin Y
  Serial.print("\tY: ");
  Serial.print(analogRead(Y));
  // Output digital readings of pin SW (button)
  Serial.print("\tButton: ");
  Serial.println(digitalRead(SW));
  // Delay for 10 milliseconds
  delay(10);
}
