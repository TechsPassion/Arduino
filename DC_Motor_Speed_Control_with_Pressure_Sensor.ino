/*
  H-Bridge L298N
  IN1 To D8
  IN2 To D9
  ENA To D10 PWM
  OUT1 & OUT2 To DC Motor
  +5V To Motor power
  GND To GND with Arduino

  Pressure Sensor
  Leg1 To +5V
  Leg2 To 10kΩ resistor To GND
  Leg2 To A0

  LED- To GND
  LED+ To D10
*/

const int IN1 = 8;
const int IN2 = 9;
const int ENA = 10;          // Motor speed control (PWM pin)
const int pressurePin = A0;  // Analog input from pressure sensor

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Set motor to rotate in one direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Read analog value from pressure sensor (0–1023)
  int pressureValue = analogRead(pressurePin);

  // Map the pressure value to motor speed (0–255)
  int motorSpeed = map(pressureValue, 0, 1023, 0, 255);

  // Set motor speed via PWM signal
  analogWrite(ENA, motorSpeed);

  delay(50);  // Short delay
}
