// Define the analog pin for the water sensor and the digital pin for the buzzer and LEDs
const int waterSensorPin = A1;
const int buzzerPin = 11;
const int redPin = 2;
const int greenPin = 3;

// Set the water level threshold to trigger the buzzer
const int waterLevelThreshold = 500;  // Adjust this value based on your sensor's calibration

// Variable to store the sensor value
int waterLevelValue = 0;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the buzzer and LEDs pin as an output
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // Read the analog value from the water sensor
  waterLevelValue = analogRead(waterSensorPin);

  // Print the water level value to the serial monitor
  Serial.print("Water Level: ");
  Serial.println(waterLevelValue);

  // Check if the water level exceeds the threshold
  if (waterLevelValue > waterLevelThreshold) {
    // Turn on the buzzer/led if water is detected
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  } else {
    // Turn off the buzzer/led if no water is detected
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  // Add a small delay for stability
  delay(100);
}
